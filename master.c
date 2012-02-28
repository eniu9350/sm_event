#include "master.h"

#include "demul.h"
#include "thread.h"
#include "common.h"
#include "connection.h"
#include "decoder_rtsp.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int master_main()
{
	int listenfd;
	int acceptfd;
	int demulfd;
	struct sockaddr_in hostaddr;
	struct sockaddr_in cliaddr;
	socklen_t cliaddr_len;


	struct epoll_event* events;
	int nfired;
	int i;
	int rrid;

	worker_threads* wts;
	worker_thread* wt;
	conn* c;

	//test
	pthread_mutex_t l;
	pthread_mutex_init(&l, NULL);
	printf("before lock---\n");
	pthread_mutex_lock(&l);
	printf("after lock---\n");
	pthread_mutex_unlock(&l);

	//------ init worker threads ---------------------
	wts = worker_threads_create(3);
	worker_threads_start(wts);

	//------ init master thread ----------------------
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	setnonblocking(listenfd);
	//mmm:should check, see sm_bak net.c

	bzero(&hostaddr, sizeof(hostaddr));
	hostaddr.sin_family = AF_INET;
	hostaddr.sin_port = htons(554);
	hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd, (struct sockaddr*)&hostaddr, sizeof(hostaddr)) == -1)	{
		close(listenfd);
		perror("bind error in master_main()!\n");
		return -1;
	}

	if(listen(listenfd, 511) == -1)	{
		close(listenfd);
		perror("listen error in master_main()!\n");
		return -1;
	}



	demulfd = demul_init(100);
	demul_add_event(demulfd, listenfd, EPOLLIN);

	events = (struct epoll_event*)malloc(1*sizeof(struct epoll_event));	
	events[0].events = EPOLLIN;

	rrid = 0;

	//mmm:set events each round???
	while(1)	{	
		nfired = demul_poll(demulfd, (void*)events, 1, -1);

		//printf("nfired = %d, e.events = %d, e.data.fd=%d\n", nfired, events->events, events->data.fd);

		for(i=0;i<nfired;i++)	{
			if(events[i].data.fd == listenfd)	{
				printf("events@listenfd!\n");

				//accept
				acceptfd = accept(events[i].data.fd, (struct sockaddr*)&cliaddr, &cliaddr_len);
				if(acceptfd == -1)	{
					perror("error while accepting(master thread)");
				}
				setnonblocking(acceptfd);	//mmm:VIP!!! //check null!

				//dispatch to worker thread
				printf("rrid = %d\n", rrid%wts->size);
				wt = wts->threads[rrid%wts->size];

				//push conn
				c = conn_init();
				c->type = CONN_TYPE_TCP;
				c->longconn = CONN_LONG;
				c->client = CONN_SERVER;
				c->fd = acceptfd;
				//c->handle = ((void*)(struct worker_thread*, int, msg_buf*))decode;
				c->handle = decode;
				//printf("accepted!!!, accfd=%d,lockq=%d\n",acceptfd, &wt->cq->lock);
				conn_queue_push(wt->cq, c);

				//notify
				if(write(wt->notify_pipe_send, "", 1) != 1)	{
					perror("writing to pipe failed!");
				}
			}
			else	{
				printf("events@other fd!\n");
			}
			rrid++;
		}
	}

	printf("end\n");

	return 0;
}

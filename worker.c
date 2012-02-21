#include "thread.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/epoll.h>


/*------ thread related def -------------------------------*/
			


worker_thread* worker_thread_create(int id)
{
	worker_thread* wt;
	int pipefd[2];

	wt = (worker_thread*)malloc(sizeof(worker_thread));
	wt->id = id;
	wt->cq = conn_queue_init();

	if(pipe(pipefd))	{
		perror("can't create pipe in worker_thread_create!");
		exit(1);
	}
	wt->notify_pipe_send = pipefd[1];
	wt->notify_pipe_receive = pipefd[0];

	return wt;
}

void worker_thread_cb_newconn(void* thisthread)
{
	conn* c;
	worker_thread* wt = (worker_thread*)thisthread;
	char buf[1];

	if(read(wt->notify_pipe_receive, buf, 1)!=1)	{//not 1 byte
	//mmm: make clear of read parameters!
		perror("not 1 byte! => not new conn! (woker_thread_cb_newconn)");
		exit(1);//mmm: exit thread or process?
	}

	c = conn_queue_pop(wt->cq);
}


worker_threads* worker_threads_create(int size)
{
	worker_threads* wts;
	worker_thread* wt;
	int i;
	wts = (worker_threads*)malloc(sizeof(worker_threads));
	wts->threads = (worker_thread*)malloc(size*sizeof(worker_thread));
	for(i=0;i<size;i++)	{
		wt = worker_thread_create(i);
		wt->id = i;
		wts->threads[i] = wt;
	}	
	wts->size = size;
	return wts;
}

int worker_threads_start(worker_threads* wts)
{
	int i;
	pthread_t* tinfos = (pthread_t*)malloc(wts->size*sizeof(pthread_t));
	pthread_attr_t* tattrs = (pthread_attr_t*)malloc(wts->size*sizeof(pthread_attr_t));
	for(i=0;i<wts->size;i++)	{
		printf("create thread %d\n", i);
		pthread_create(tinfos+i, tattrs+i, worker_main, wts->threads[i]);
	}
}
/*------ function of worker --------------------------*/
static void* worker_main(void* arg)
{
	worker_thread* wt = (worker_thread*)arg;

	int demulfd;
	struct epoll_event* events;
	int nfired;
	int i;

	printf("worker thread %d start\n", wt->id);

	demulfd = demul_init(100);	//mmm:100?
	demul_add_event(demulfd, wt->notify_pipe_receive, EPOLLIN);
	printf("event added, notifyfd=%d\n", wt->notify_pipe_receive);

	events = (struct epoll_event*)malloc(1*sizeof(struct epoll_event));	
	events[0].events = EPOLLIN;

	//	epoll
	printf("-----------------epoll here\n");
	for(;;)	{
		nfired = demul_poll(demulfd, (void*)events, 1, -1);
		printf("------------eventfd here!\n");
		for(i=0;i<nfired;i++)	{
		if(events[i].data.fd = wt->notify_pipe_receive)	{
			printf("notification received!");
		}
		else	{
			
		}
		}
	}
}

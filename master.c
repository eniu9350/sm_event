#include "master.h"

#include "demul.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int master_main()
{
	int listenfd;
	int demulfd;
	struct sockaddr_in hostaddr;

	struct epoll_event* events;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
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

	demul_poll(demulfd, (void*)events, 1, -1);
	
	printf("end\n");

	return 0;
}

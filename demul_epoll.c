#include "demul.h"

#include <sys/epoll.h>
#include <stdio.h>

int demul_init(int size)
{
	return epoll_create(size);
}


int demul_add_event(int demulfd, int fd, int mask)
{
	//mmm: should check first, maybe op is MOD rather than ADD!
	struct epoll_event e;
	e.events = mask;
	e.data.u64 = 0; //mmm: why? see redis
	e.data.fd = fd;	//mmm: useful?
	printf("in add_event\n");
	if(epoll_ctl(demulfd, EPOLL_CTL_ADD, fd, &e) == -1)	{
		return -1;
	}
	return 0;
}

void demul_poll(int demulfd, void* events, int maxevents, int timeout)
{
	struct epoll_event* epevents = (struct epoll_event*)events;
	epoll_wait(demulfd, epevents, maxevents, timeout);
}

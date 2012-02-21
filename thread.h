#ifndef _SM_THREAD_
#define _SM_THREAD_

#include <pthread.h>

typedef struct {
	int fd;
} conn;

typedef struct {
	conn* head;
	conn* tail;
	pthread_mutex_t lock;
} cq;
	

#endif

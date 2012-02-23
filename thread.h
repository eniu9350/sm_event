#ifndef _SM_THREAD_
#define _SM_THREAD_

#include <pthread.h>

#include "common.h"
#include "connection.h"

typedef struct conn_queue conn_queue;	//mmm: redeclared, ok?

/*------ worker thread related ----------------------------*/
typedef struct {
	int id;	//configured manually
	pthread_t t;
	conn_queue* cq;	//mmm: must use struct! why?
	int notify_pipe_send;
	int notify_pipe_receive;
	msg_buf* buf_cli;	//cient buf
} worker_thread;

typedef struct {
	worker_thread** threads;
	int size;
}worker_threads;

worker_thread* worker_thread_create(int id);
void worker_thread_cb_newconn(void* thisthread);

worker_threads* worker_threads_create(int size);

static void* worker_main(void* arg);

#endif

#ifndef _SM_THREAD_
#define _SM_THREAD_

#include <pthread.h>

#include "common.h"

/*------ thread utilities ---------------------------------*/
typedef struct conn{
	int fd;
	struct conn* next;
} conn;

typedef struct {
	conn* head;
	conn* tail;
	pthread_mutex_t lock;
} conn_queue;

conn_queue* conn_queue_init();

int conn_queue_push(conn_queue* cq, conn* c);
conn* conn_queue_pop(conn_queue* cq);

/*------ worker thread related ----------------------------*/
typedef struct {
	int id;	//configured manually
	pthread_t t;
	conn_queue* cq;
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

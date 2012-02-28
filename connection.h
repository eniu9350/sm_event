#ifndef _SM_CONNECTION_
#define _SM_CONNECTION_

#include <pthread.h>

#include "common.h"
//#include "thread.h"
#include "msg_rtsp.h"

#define CONN_TYPE_TCP 1
#define CONN_TYPE_UDP 2

//only vaid to tcp
#define CONN_LONG 1
#define CONN_SHORT 2

#define CONN_CLIENT 1
#define CONN_SERVER 2

struct worker_thread;

typedef struct conn{
	//---- some flags ---
	int type;
	int longconn;
	//int reconn;
	int client;

	//---- important stuff
	int fd;
	msg_buf* buf;	
	void (*handle)(struct worker_thread* wt, int fd, msg_buf* buf);

	struct conn* next;
} conn;

typedef struct conn_queue{
	conn* head;
	conn* tail;
	pthread_mutex_t lock;
} conn_queue;

/*------ connection operations ---------------------------------*/
conn* conn_init();


/*------ connection queue operations ---------------------------------*/
conn_queue* conn_queue_init();
int conn_queue_push(conn_queue* cq, conn* c);
conn* conn_queue_pop(conn_queue* cq);


#endif

#include "connection.h"

#include <stdio.h>
#include <stdlib.h>


/*------ connection utilities ---------------------------------*/
conn_queue* conn_queue_init()
{
	conn_queue* cq = (conn_queue*)malloc(sizeof(conn_queue));
	int status;
	cq->head = NULL;
	cq->tail = NULL;
	status = pthread_mutex_init(&cq->lock, NULL);
	//printf("mutex init status=%d\n",status);

	return cq;
}

int conn_queue_push(conn_queue* cq, conn* c)
{
	c->next = NULL;

	printf("push before lock\n");
	//printf("lockp=%d\n", &cq->lock);
	//printf("push before lock, lockp=%d\n", &cq->lock);
	pthread_mutex_lock(&cq->lock);
	printf("push lock acquired\n");
	if(cq->tail==NULL)	{
		cq->head = c;
	}
	else	{
		cq->tail->next = c;
	}
	cq->tail = c;
	pthread_mutex_unlock(&cq->lock);

	return 0;
}

conn* conn_queue_pop(conn_queue* cq)
{
	conn* c;

	pthread_mutex_lock(&cq->lock);
	c = cq->head;
	if(c!=NULL)	{
		cq->head = c->next;
		if(c->next == NULL)	{
			cq->tail = NULL;
		}
	}
	pthread_mutex_unlock(&cq->lock);
	printf("conn q pop\n");
	return c;
}

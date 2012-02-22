#include "common.h"

#include <stdlib.h>
#include <fcntl.h>

str* str_create(int len)
{
	str* s = (str*)malloc(sizeof(str));
	s->s = (char*)malloc(len*sizeof(char));
	s->len = len;
	return s;
}

void str_show(str* s)
{
	int i;
	for(i=0;i<s->len;i++)	{
		putchar(s->s[i]);
	}
	putchar('\n');
}

msg_buf* msg_buf_create(int size)
{
	msg_buf* buf;
	if(size<1)	{
		perror("msg_buf_create init size should be 1 at least");
		return NULL;
	}
	buf = (msg_buf*)malloc(sizeof(msg_buf));
	buf->size = size;
	buf->data = (char*)malloc(size*sizeof(char));
	buf->start = 0;
	buf->end = 0;
	return buf;
}

//设置socket连接为非阻塞模式  
void setnonblocking(int sockfd) {  
	int opts;  

	opts = fcntl(sockfd, F_GETFL);  
	if(opts < 0) {  
		perror("fcntl(F_GETFL)\n");  
		exit(1);  
	}  
	opts = (opts | O_NONBLOCK);  
	if(fcntl(sockfd, F_SETFL, opts) < 0) {  
		perror("fcntl(F_SETFL)\n");  
		exit(1);  
	}  
}  

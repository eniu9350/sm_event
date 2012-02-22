#include "common.h"

#include <stdlib.h>
#include <fcntl.h>

msg_buf* msg_buf_create(int size)
{
	msg_buf* buf;
	buf = (msg_buf*)malloc(sizeof(msg_buf));
	buf->size = size;
	buf->data = (char*)malloc(size*sizeof(char));
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

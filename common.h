#ifndef _SM_COMMON_
#define _SM_COMMON_

typedef struct msg_buf	{
		char* data;
		int size;
} msg_buf;


msg_buf* msg_buf_create(int size);
void setnonblocking(int sockfd);
#endif

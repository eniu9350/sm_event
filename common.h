#ifndef _SM_COMMON_
#define _SM_COMMON_

typedef struct str	{
	char* s;
	int len;
}str;

typedef struct msg_buf	{
		char* data;
		int size;
		int start;
		int end;
} msg_buf;


str* str_create(int len);
void str_show(str* s);

msg_buf* msg_buf_create(int size);

void setnonblocking(int sockfd);
#endif

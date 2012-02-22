#include "decoder_rtsp.h"

#include "msg_rtsp.h"

#include <stdio.h>
#include <stdlib.h>

//only for worker_thread use!
msg_rtsp* decode(worker_thread* wt, int fd, msg_buf* buf)
{
	msg_rtsp* msg;
	char* s;
	char* p;
	int nread, n;
	int flag;
	char* start;

	msg_rtsp_header_fline* fline;

	msg = (msg_rtsp*)malloc(sizeof(msg_rtsp));

	printf("decode 1 begin!\n");

	//read all
	nread = 0;
	while( (n=read(fd, buf->data+buf->end+nread, buf->size-buf->end-nread-1)) > 0)	{
		nread += n;
	}
	buf->end = buf->end + nread;
	printf("decode 2 read all! nread=%d\n", nread);

	//parse first line to get msg type
	p = s = buf->data+buf->start;
	flag = 0;
	while(p<buf->data+buf->end)	{
		if(*p=='\r' && *(p+1)=='\n')	{
			flag = 1;
			break;
		}
		p++;
	}
	printf("decode 3 firstline!\n");
	if(!flag)	{	//no CRLF, wait for more data
		printf("no CRLF in firstline!\n");
		return NULL;
	}
	p = p+2; //skip CRLF
	printf("yes CRLF in firstline!\n");

	fline = (msg_rtsp_header_fline*)malloc(sizeof(msg_rtsp_header_fline));
	fline->line = str_create(p-s);
	memcpy((void*)fline->line->s, (void*)s, p-s);
	str_show(fline->line);
	if(fline->line->s[0] >= 'A' && fline->line->s[0] <= 'Z')	{
		msg->type = RTSP_REQUEST;
	} else if(fline->line->s[0] >= '0' && fline->line->s[0] <= '9')	{
		msg->type = RTSP_RESPONSE;
	}	else	{
		perror("rsp msg type unknown!");
	}
	msg->fline = fline;
	msg_rtsp_show(msg);
	

	//-------------------for test ---------------------------
	printf("decode end, buf:\n");
	buf->data[buf->size-1] = '\0';
	printf("%s\n", buf->data);
}

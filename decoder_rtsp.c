#include "decoder_rtsp.h"

#include "msg_rtsp.h"

#include <stdio.h>
#include <stdlib.h>

//only for worker_thread use!
msg_rtsp* decode(worker_thread* wt, int fd, msg_buf* buf)
{
	msg_rtsp* msg;
	int nread, n;

	msg = (msg_rtsp*)malloc(sizeof(msg_rtsp));

	nread = 0;
	//while( (n=read(fd, buf+nread, buf->size)) > 0)	{
	while( (n=read(fd, buf+nread, buf->size-nread-1)) > 0)	{
		nread += n;
		printf("===read=== n=%d, nread=%d, toread=%d\n", n, nread, buf->size-nread-1+n);
	}
	printf("decode end\n");
}

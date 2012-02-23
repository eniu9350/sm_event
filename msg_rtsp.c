#include "msg_rtsp.h"

#include <stdio.h>
#include <string.h>

void msg_rtsp_show(msg_rtsp* msg)
{
	char s[100];
	printf("[TYPE] ");
	if(msg->type == RTSP_REQUEST)	{
		printf("REQ\n");
	}
	else if(msg->type == RTSP_RESPONSE)	{
		printf("RESP\n");
	}
	printf("[FLINE] ");
	memcpy(s, msg->fline->line->s, msg->fline->line->len);
	s[msg->fline->line->len-1] = '\0';
	printf("%s\n", s);
}

#ifndef _SM_MSG_RTSP_
#define _SM_MSG_RTSP_

#include "common.h"


#define RTSP_REQUEST 1
#define RTSP_RESPONSE 2
typedef int msg_rtsp_type;

typedef struct msg_rtsp_header_reqline	{
}msg_rtsp_header_reqline;

typedef struct msg_rtsp_header_statline	{
}msg_rtsp_header_statline;

typedef struct msg_rtsp_header_fline	{
	str* line;
	union	{
		msg_rtsp_header_reqline reqline;
		msg_rtsp_header_statline statline;
	}u;
}msg_rtsp_header_fline;//first line

typedef struct msg_rtsp_header_field	{
	str* key;
	str* val;
	int len;	//including CRLF
}msg_rtsp_header_field;
	
typedef struct msg_rtsp	{
	msg_rtsp_type type;
	msg_rtsp_header_fline* fline;
	msg_rtsp_header_field* cseq;
} msg_rtsp;

void msg_rtsp_show(msg_rtsp* msg);

#endif

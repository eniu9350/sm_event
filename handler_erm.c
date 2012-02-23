#include "handler_erm.h"

#include <stdio.h>


static void on_setup_resp(msg_rtsp* msg)
{
}

static void on_teardown_resp(msg_rtsp* msg)
{
}

static void on_getparameter_resp(msg_rtsp* msg)
{
}

void handle_erm(worker_thread* wt, msg_rtsp* msg)
{
	printf("in handle_erm\n");
	
}

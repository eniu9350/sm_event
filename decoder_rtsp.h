#ifndef _SM_DECODER_RTSP_
#define _SM_DECODER_RTSP_

#include "msg_rtsp.h"

#include "thread.h"

msg_rtsp* decode_rtsp(worker_thread* wt, int fd, msg_buf* buf);


#endif

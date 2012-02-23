CC = gcc

test:
	$(CC) common.c demul_epoll.c msg_rtsp.c connection.c thread.c worker.c decoder_rtsp.c handler_erm.c master.c test.c -lpthread

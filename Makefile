CC = gcc

test:
	$(CC) common.c demul_epoll.c thread.c decoder_rtsp.c msg_rtsp.c worker.c master.c test.c -lpthread

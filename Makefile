CC = gcc

test:
	$(CC) demul_epoll.c thread.c worker.c master.c test.c -lpthread

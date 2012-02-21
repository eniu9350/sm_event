CC = gcc

test:
	$(CC) -lpthread demul_epoll.c master.c test.c

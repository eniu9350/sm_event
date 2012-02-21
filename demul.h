#ifndef _SM_DEMUL_
#define _SM_DEMUL_

int demul_init(int size);

//mmm: return value meaning unified?
int demul_poll(int demulfd, void* events, int maxevents, int timeout);

int demul_add_event(int demulfd, int fd, int mask);

#endif

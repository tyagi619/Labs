#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

void *mk(void);

int size(void *);

void insert(void *QP,long key,void *elem);

void *removeQ(void *QP,long key);

void add_start(void *QP,void *elem,long key);

void add_end(void *QP,void *elem,long key);

void *del_start(void *);

void *del_end(void *);

void *duplicate(void *);


#endif

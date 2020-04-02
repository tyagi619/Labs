#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

void *mklist(void);

void push(void *QP,void *elem,long key);

void *pop(void *QP,long key);

#endif

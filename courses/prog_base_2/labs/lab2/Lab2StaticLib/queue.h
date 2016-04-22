#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>

typedef struct queue_s queue_t;

queue_t * queue_new(void);
void queue_free(queue_t * self);

int queue_getElement(queue_t * self, int index);
void queue_add(queue_t * self, int val);
int queue_delete(queue_t * self);
int queue_getCount(queue_t * self);

void queue_print(queue_t * self);

#endif // QUEUE_H_INCLUDED

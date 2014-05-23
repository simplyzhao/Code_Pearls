#ifndef __QUEUE_H
#define __QUEUE_H

/* 
 * implementation of queue
 * Note: 
 * you have to take care of the memory thing completely by yourself
 * here in queue, we just store the pointer in container, and then remove it,
 * queue itself will not delete the memory related to the pointer
 */

#include "basic.h"

struct Queue;

struct Queue *create_queue();
void destroy_queue(struct Queue *);

BOOL queue_push(struct Queue *, void *);
BOOL queue_pop(struct Queue *);

void *queue_front(struct Queue *);
int queue_count(struct Queue *);
BOOL queue_is_empty(struct Queue *);

#endif

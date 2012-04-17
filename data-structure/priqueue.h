#ifndef __PRIQUEUE_H
#define __PRIQUEUE_H

/* 
 * implementation of priority queue using minimal-heap 
 * Note: 
 * you have to take care of the memory thing completely by yourself
 * here in heap, we just store the pointer in container, and then remove it,
 * heap itself will not delete the memory related to the pointer
 */
#include "basic.h"

struct PriQueue;

struct PriQueue *create_priqueue(int, compare_func);
void destroy_priqueue(struct PriQueue *);

BOOL priqueue_insert(struct PriQueue *, void *);
void *priqueue_extract(struct PriQueue *);

int priqueue_count(struct PriQueue *);
BOOL priqueue_is_empty(struct PriQueue *);

#endif

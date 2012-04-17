#ifndef __HEAP_H
#define __HEAP_H

/* 
 * implementation of minimal heap 
 * Note: 
 * you have to take care of the memory thing completely by yourself
 * here, we just store the pointer in container, and then remove it,
 */
#include "basic.h"
#include "vector.h"

struct Heap;

struct Heap *create_heap(int, compare_func);
struct Heap *create_heap_from_vector(struct Vector *, compare_func);
void destroy_heap(struct Heap *);

BOOL heap_push(struct Heap *, void *);
BOOL heap_pop(struct Heap *);
void *heap_top(struct Heap *);

int heap_count(struct Heap *);
BOOL heap_is_empty(struct Heap *);

static void heap_shift_up(struct Heap *, int);
static void heap_shift_down(struct Heap *, int);
#endif 

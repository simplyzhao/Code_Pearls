#ifndef __STACK_H
#define __STACK_H

/* 
 * implementation of stack
 * Note: 
 * you have to take care of the memory thing completely by yourself
 * here in stack, we just store the pointer in container, and then remove it,
 * stack itself will not delete the memory related to the pointer
 */
#include "basic.h"

struct Stack;

struct Stack *create_stack(int capacity);
void destroy_stack(struct Stack *);

BOOL stack_push(struct Stack *, void *);
BOOL stack_pop(struct Stack *);

void *stack_top(struct Stack *);
int stack_count(struct Stack *);
BOOL stack_is_empty(struct Stack *);

#endif

#include "stack.h"
#include "vector.h"

struct Stack {
	struct Vector *vector;
};

struct Stack *
create_stack(int capacity)
{
	struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
	if(stack) {
		struct Vector *v = create_vector(capacity, NULL);
		if(v != NULL)
			stack->vector = v;
		else {
			free(stack);
			stack = NULL;
		}
	}
	return stack;
}

void 
destroy_stack(struct Stack *stack)
{
	if(stack) {
		if(stack->vector)
			destroy_vector(stack->vector, FALSE);

		free(stack);
	}
}

BOOL
stack_push(struct Stack *stack, void *data)
{
	assert(stack != NULL);
	return vector_push_back(stack->vector, data);
}

BOOL
stack_pop(struct Stack *stack)
{
	assert(stack != NULL);
	if(stack_is_empty(stack))
		return FALSE;
	return vector_remove_at(stack->vector, (vector_count(stack->vector)-1), FALSE);
}

void *
stack_top(struct Stack *stack)
{
	assert(stack != NULL);
	if(stack_is_empty(stack))
		return NULL;
	return vector_at(stack->vector, (vector_count(stack->vector)-1));
}

int
stack_count(struct Stack *stack)
{
	assert(stack != NULL);
	return vector_count(stack->vector);
}

BOOL
stack_is_empty(struct Stack *stack)
{
	assert(stack != NULL);
	return (vector_count(stack->vector) == 0);
}

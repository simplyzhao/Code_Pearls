#include "stack.h"

int
main(int argc, char **argv)
{
	struct Stack *stack = create_stack(3);

	stack_push(stack, "Julie");
	stack_push(stack, "Joey");
	stack_push(stack, "Joseph");
	stack_push(stack, "Jane");

	while(!stack_is_empty(stack)) {
		printf("%d\n", stack_count(stack));
		printf("%s\n", (char *)stack_top(stack));
		stack_pop(stack);
	}

	destroy_stack(stack);
}

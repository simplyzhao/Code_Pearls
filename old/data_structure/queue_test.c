#include "queue.h"

int
main(int argc, char **argv)
{
	struct Queue *queue = create_queue();

	queue_push(queue, "Julie");
	queue_push(queue, "Joey");
	queue_push(queue, "Joseph");
	queue_push(queue, "Jane");

	while(!queue_is_empty(queue)) {
		printf("%d\n", queue_count(queue));
		printf("%s\n", (char *)queue_front(queue));
		queue_pop(queue);
	}

	destroy_queue(queue);
}

#include "queue.h"
#include "list.h"

struct Queue {
	struct List *list;
};

struct Queue *
create_queue()
{
	struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
	if(queue) {
		struct List *l = create_list(NULL);
		if(l != NULL) {
			queue->list = l;
		} else {
			free(queue);
			queue = NULL;
		}
	}
	return queue;
}

void
destroy_queue(struct Queue *queue)
{
	if(queue) {
		if(queue->list)
			destroy_list(queue->list, FALSE);

		free(queue);
	}
}

BOOL
queue_push(struct Queue *queue, void *data)
{
	assert(queue != NULL);
	return list_push_back(queue->list, data);
}

BOOL
queue_pop(struct Queue *queue)
{
	assert(queue != NULL);

	if(queue_is_empty(queue))
		return FALSE;
	return list_remove_node(queue->list, list_head(queue->list), FALSE);
}

void *
queue_front(struct Queue *queue)
{
	assert(queue != NULL);

	if(queue_is_empty(queue))
		return NULL;
	return (list_head(queue->list)->val);
}

int
queue_count(struct Queue *queue)
{
	assert(queue != NULL);
	return list_count(queue->list);
}

BOOL
queue_is_empty(struct Queue *queue)
{
	assert(queue != NULL);
	return (list_count(queue->list) == 0);
}

#include "priqueue.h"
#include "heap.h"


struct PriQueue {
	struct Heap *heap;
};

struct PriQueue *
create_priqueue(int capacity, compare_func compare)
{
	struct PriQueue *priqueue = (struct PriQueue *)malloc(sizeof(struct PriQueue));
	if(priqueue) {
		struct Heap *hp = create_heap(capacity, compare);
		if(hp == NULL) {
			free(priqueue);
			priqueue = NULL;
		} else
			priqueue->heap = hp;
	}
	return priqueue;
}

void
destroy_priqueue(struct PriQueue *priqueue)
{
	if(priqueue) {
		if(priqueue->heap)
			destroy_heap(priqueue->heap);
	}
	free(priqueue);
}

BOOL
priqueue_insert(struct PriQueue *priqueue, void *data)
{
	assert(priqueue != NULL);
	return heap_push(priqueue->heap, data);
}

void *
priqueue_extract(struct PriQueue *priqueue)
{
	assert(priqueue != NULL);
	void *ret = heap_top(priqueue->heap);
	heap_pop(priqueue->heap);
	return ret;
}

int
priqueue_count(struct PriQueue *priqueue)
{
	assert(priqueue != NULL);
	return heap_count(priqueue->heap);
}

BOOL
priqueue_is_empty(struct PriQueue *priqueue)
{
	assert(priqueue != NULL);
	return heap_is_empty(priqueue->heap);
}

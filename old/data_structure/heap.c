#include "heap.h"

/* consider vector as a tree, index starts from zero */
#define LEFT(i) (((i)<<1)+1)
#define RIGHT(i) (((i)+1)<<1)
#define PARENT(i) (((i)-1)>>1)

struct Heap {
	struct Vector *vector;
	compare_func compare;
};

struct Heap *
create_heap(int capacity, compare_func comp)
{	
	struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
	if(heap) {
		struct Vector *v = create_vector(capacity, NULL);
		if(v==NULL || comp==NULL) {
			free(heap);
			heap = NULL;
		} else {
			heap->vector = v;
			heap->compare = comp;
		}
	}
	return heap;
}

struct Heap *
create_heap_from_vector(struct Vector *v, compare_func comp)
{
	if(v==NULL || comp==NULL)
		return NULL;
	struct Vector *vd = vector_duplicate(v);
	if(vd == NULL)
		return NULL;
	struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
	if(heap) {
		heap->vector = vd;
		heap->compare = comp;

		int index;
		for(index=(vector_count(v)>>1); index>=0; --index)
			heap_shift_down(heap, index);
	} else {
		destroy_vector(vd, FALSE);
	}
	return heap;
}

void
destroy_heap(struct Heap *heap)
{	
	if(heap) {
		if(heap->vector)
			destroy_vector(heap->vector, FALSE); 

		free(heap);
	}
}

static void 
heap_shift_up(struct Heap *heap, int index)
{	
	/*
	 * precondition: vector[0..index-1] -- heap
	 * postcondition: vector[0..index] -- heap
	 * time: O(logN)
	 */
	int parent, child = index;
	while(child > 0) {
		parent = PARENT(child);
		if(heap->compare(vector_at(heap->vector, child), vector_at(heap->vector, parent)) < 0) {
			vector_exchange(heap->vector, child, parent);
			child = parent;
		} else
			break;
	}
	return;
}

static void 
heap_shift_down(struct Heap *heap, int index)
{	
	/*
	 * precondition: vector[LEFT(index)..end] -- heap, and
	 *				 vector[RIGHT(index)..end] -- heap
	 * postcondition: vector[index..end] --heap
	 * time: O(logN)
	 */
	int left, right, smallest = index;
	left = LEFT(index);
	right = RIGHT(index);
	if(left<heap_count(heap) && 
			heap->compare(vector_at(heap->vector, smallest), vector_at(heap->vector, left))>0)
		smallest = left;
	if(right<heap_count(heap) &&
			heap->compare(vector_at(heap->vector, smallest), vector_at(heap->vector, right))>0)
		smallest = right;
	if(smallest != index) {
		vector_exchange(heap->vector, index, smallest);
		heap_shift_down(heap, smallest);
	}
}


BOOL
heap_push(struct Heap *heap, void *data)
{
	assert(heap != NULL);
	vector_push_back(heap->vector, data);
	heap_shift_up(heap, (vector_count(heap->vector)-1));
}

BOOL
heap_pop(struct Heap *heap)
{
	assert(heap != NULL);
	if(heap_is_empty(heap))
		return FALSE;

	vector_exchange(heap->vector, 0, (vector_count(heap->vector)-1));
	vector_remove_at(heap->vector, (vector_count(heap->vector)-1), FALSE);
	heap_shift_down(heap, 0);
}

void *
heap_top(struct Heap *heap)
{
	assert(heap != NULL);
	if(heap_is_empty(heap))
		return NULL;

	return vector_at(heap->vector, 0);
}

int
heap_count(struct Heap *heap)
{
	assert(heap != NULL);
	return (vector_count(heap->vector));
}

BOOL
heap_is_empty(struct Heap *heap)
{
	assert(heap != NULL);
	return ((vector_count(heap->vector)) == 0);
}

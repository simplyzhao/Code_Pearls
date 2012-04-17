#include "heap.h"
#include "vector.h"

int
compare(const void *arg1, const void *arg2)
{
	return strcmp((char *)arg1, (char *)arg2);
}

int
main(int argc, char **argv)
{
	char *a = strdup("Nokia");
	char *b = strdup("Apple");
	char *c = strdup("HTC");
	char *d = strdup("Moto");
	char *e = strdup("Samsung");
	char *f = strdup("Who's best");
	char *g = strdup("No doubtly, Apple");
	
	struct Vector *v = create_vector(0, free);
	vector_push_back(v, a);
	vector_push_back(v, b);
	vector_push_back(v, c);
	vector_push_back(v, d);
	vector_push_back(v, e);

	struct Heap *heap = create_heap_from_vector(v, compare);

	heap_push(heap, f);
	heap_push(heap, g);

	while(!heap_is_empty(heap)) {
		printf("%d\n", heap_count(heap));
		printf("%s\n", (char *)heap_top(heap));
		heap_pop(heap);
	}

	destroy_heap(heap);
	destroy_vector(v, TRUE);
	free(f);
	free(g);
}

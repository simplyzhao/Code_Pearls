#include "vector.h"

int
compare(const void *arg1, const void *arg2)
{
	return *(int *)arg1 - *(int *)arg2;
}

void
print(const void *arg)
{
	printf("%d\n", *(int *)arg);
}

int
main(int argc, char **argv)
{
	int *a, *b, *c, *d, *e, *f, *g;
	a = (int *)malloc(sizeof(int));
	b = (int *)malloc(sizeof(int));
	c = (int *)malloc(sizeof(int));
	d = (int *)malloc(sizeof(int));
	e = (int *)malloc(sizeof(int));
	f = (int *)malloc(sizeof(int));
	g = (int *)malloc(sizeof(int));
	*a = 6;
	*b = 1;
	*c = 99;
	*d = -17;
	*e = 22;
	*f = 9;
	*g = 6;

	struct Vector *iv = create_vector(2, free);
	vector_push_back(iv, a);
	vector_push_back(iv, b);
	vector_push_back(iv, c);
	vector_push_back(iv, d);
	vector_push_front(iv, e);
	vector_push_front(iv, f);
	vector_insert(iv, g, 5);

	vector_foreach(iv, print);
	printf("\nCount: %d, Capacity: %d--------------\n", vector_count(iv), vector_capacity(iv));

	printf("%d\n", *f);
	vector_remove(iv, f, compare, TRUE);
	vector_foreach(iv, print);
	printf("\nCount: %d, Capacity: %d--------------\n", vector_count(iv), vector_capacity(iv));

	vector_sort(iv, compare);
	vector_foreach(iv, print);
	printf("\nCount: %d, Capacity: %d--------------\n", vector_count(iv), vector_capacity(iv));

	printf("\nBsearch: %d, Lower: %d, Upper: %d\n", vector_bsearch(iv, a, compare), 
			vector_lower(iv, a, compare), vector_upper(iv, a, compare));

	vector_shuffle(iv);
	vector_foreach(iv, print);
	printf("\nCount: %d, Capacity: %d--------------\n", vector_count(iv), vector_capacity(iv));

	destroy_vector(iv, TRUE);
}

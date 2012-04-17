#include "bitset.h"
#include<time.h>

/* generate random numbers between 0 and LIMIT, sort them with bitset */

#define LIMIT 500
#define ARRAY_SIZE 15

int array[ARRAY_SIZE];

void
swap(int *arr, int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void
generate_array()
{
	int i, tmp[LIMIT];
	for(i=0; i<LIMIT; ++i)
		tmp[i] = i;
	/* shuffle */
	srand(time(NULL));
	for(i=LIMIT-1; i>0; --i)
		swap(tmp, i, rand()%(i+1));

	memcpy(array, tmp, sizeof(int)*ARRAY_SIZE);

	for(i=0; i<ARRAY_SIZE; ++i)
		printf("%d\t", array[i]);
	printf("\n");
}

int
main(int argc, char **argv)
{
	generate_array();

	struct Bitset *bitset = create_bitset(LIMIT);
	int i;
	for(i=0; i<ARRAY_SIZE; ++i)
		bitset_set(bitset, array[i]);

	for(i=0; i<LIMIT; ++i)
		if(bitset_test(bitset, i))
			printf("%d\t", i);
	printf("\n");

	destroy_bitset(bitset);
}

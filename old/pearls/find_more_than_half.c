/* 
 * Problem:
 *   given you an integer array, in which there's an specific integer appearing
 *   more than half of total number of integers, find it.
 *
 * See: <bop> 2.3
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 10000
long total, id[MAX_NUM];

void
init()
{
	long i;
	scanf("%ld", &total);
	for(i=0; i<total; ++i)
		scanf("%ld", id+i);
}

int
compare(const void *arg1, const void *arg2)
{
	return (*(long *)arg1 - *(long *)arg2);
}

long
method_nlogn()
{
	qsort(id, total, sizeof(long), compare);
	/* sorting, and the specific id must in the middle */
	return id[total>>1]; 
}

long
method_n()
{
	long i, candidate, count = 0;
	for(i=0; i<total; ++i) {
		if(count == 0) {
			candidate = i;
			count = 1;
		} else {
			if(id[candidate] == id[i])
				++count;
			else
				--count;
		}
	}
	return id[candidate];
}

int
main(int argc, char **argv)
{
	init();
	printf("ID Looking For: %ld\n", method_n());
	return 0;
}

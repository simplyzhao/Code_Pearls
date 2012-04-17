/* water */
/* qsort, T(n) = nlogn [average]
/* Memory: 412K, Time: 47MS */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int
compare(const void *arg1, const void *arg2)
{
	return *(long *)arg1 - *(long *)arg2;
}

int
main(int argc, char **argv)
{
	int i, N;
	long *arr;

	scanf("%d", &N);
	arr = (long *)malloc(sizeof(long)*N);
	for(i=0; i<N; i++)
		scanf("%ld", arr+i);

	qsort(arr, N, sizeof(long), compare);

	printf("%ld\n", arr[(N-1)/2]);
}

/*
 * ith order statistic is the ith smallest element in Set S
 * T = O(n) [expected time]
 * Memory: 408K, Time: 32MS
 *
 * PKU can't apply random algorithm ?......
 * with random, always RE, AC without random
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void 
swap(long *arr, int i, int j)
{
	long temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

/*
int
random_index(int begin, int end)
{
	srand(time(NULL));
	return rand()%(end-begin+1)+begin;
}
*/

int 
random_partition(long *arr, int begin, int end)
{
	int i, j;
	i = begin;
	/*
	int pivot_idx = random_index(begin, end);
	int pivot_idx = begin;
	swap(arr, begin, pivot_idx);
	*/
	long pivot = arr[begin];
	for(j=begin+1; j<=end; j++)
		if(arr[j] <= pivot)
			swap(arr, ++i, j);
	swap(arr, i, begin);
	return i;
}

long
find_ith_os(long *arr, int begin, int end, int ith)
{
	if(begin == end)
		return arr[begin];
	int p = random_partition(arr, begin, end);
	int k = p-begin+1;
	if(k == ith)
		return arr[p];
	else if(ith < k)
		return find_ith_os(arr, begin, p-1, ith);
	else
		return find_ith_os(arr, p+1, end, ith-k);
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

	printf("%ld\n", find_ith_os(arr, 0, N-1, (N+1)/2));
}

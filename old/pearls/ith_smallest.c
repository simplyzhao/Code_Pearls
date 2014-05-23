/*
 * order statistic (the ith smallest element in an unordered array
 */
#include<stdio.h>
#include<stdlib.h> /* rand, srand */
#include<time.h>  /* time */

void 
swap(int *arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int 
partition(int *arr, int p, int q)
{
	int pivot = arr[q]; /* pivot */
	int i=p-1;
	int j;

	for(j=p; j<=q-1; j++) 
		if(arr[j] <= pivot) 
			swap(arr, ++i, j);

	swap(arr, i+1, q);
	return i+1;
}

int
randomized_partition(int *arr, int p, int q)
{
	srand(time(NULL));
	int r = (rand()%(q-p+1))+p;
	swap(arr, r, q);
	return partition(arr, p, q);
}

/*
 * divide and conquer algorithm
 */
int
random_select(int *arr, int p, int q, int i)
{
	int r, k;
	r = randomized_partition(arr, p, q);
	k = r-p+1;
	if(k == i)
		return arr[r];
	else if(k < i)
		return random_select(arr, r+1, q, i-k);
	else
		return random_select(arr, p, r-1, i);
}

/* -----------------------test------------------------- */
int
main(int argc, char **argv)
{
	int i;
	int arr[] = {4, 6, 2, 7, 5};
	scanf("%d", &i);
	printf("%dth smallest: %d\n", i, random_select(arr, 0, 4, i));
}
	

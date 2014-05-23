/* inversion (merge-sort) */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long long
merge_count(long *arr, long *temp, long begin, long end)
{
	if(begin >= end)
		return 0;
	long i, j, k, mid = (begin+end)/2;
	long long rt = 0;
	rt += merge_count(arr, temp, begin, mid);
	rt += merge_count(arr, temp, mid+1, end);
	i = k = begin;
	j = mid+1;
	while(i<=mid && j<=end) {
		if(arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else {
			temp[k++] = arr[j++];
			rt += (mid-i+1);
		}
	}
	for( ; i<=mid; i++)
		temp[k++] = arr[i];
	for( ; j<=end; j++) {
		temp[k++] = arr[j];
		rt += (mid-i+1);
	}
	/* copy */
	for(k=begin; k<=end; k++)
		arr[k] = temp[k];
	return rt;
}

int
main(int argc, char **argv)
{
	long i, n;
	long *arr, *temp;
	while(scanf("%ld", &n)!=EOF && n!=0) {
		arr = malloc(sizeof(long)*n);
		temp = malloc(sizeof(long)*n);
		for(i=0; i<n; i++)
			scanf("%ld", arr+i);
		printf("%lld\n", merge_count(arr, temp, 0, n-1));
		free(temp);
		free(arr);
	}
	return 0;
}

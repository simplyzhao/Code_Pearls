/*
 * similar/identical to PKU 2479
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long n;
int *arr;
/*
 * hd[i] stores the maximum sub-segment from arr[0..i]
 * tl[i] stores the maximum sub_segment from arr[i+1..n-1]
 */
long *hd, *tl;

long
max_subsum(int *arr, long N)
{
	long i, temp, max;
	/* hd */
	hd[0] = max = arr[0];
	for(i=1; i<N; i++) {
		temp = hd[i-1] + arr[i];
		hd[i] = temp>arr[i] ? temp : arr[i];
	}
	for(i=1; i<N; i++) {
		hd[i] = hd[i] > max ? hd[i] : max;
		max = hd[i];
	}
	/* tl */
	tl[N-1] = max = arr[N-1];
	for(i=N-2; i>=0; i--) {
		temp = tl[i+1] + arr[i];
		tl[i] = temp>arr[i] ? temp : arr[i];
	}
	for(i=N-2; i>=0; i--) {
		tl[i] = tl[i] > max ? tl[i] : max;
		max = tl[i];
	}
}

long
enumerate()
{
	long i, temp, max = hd[0] + tl[1];
	for(i=1; i<n-1; i++) {
		temp = hd[i] + tl[i+1];
		max = max>temp ? max : temp;
	}
	return max;
}

int
main(int argc, char **argv)
{
	long i;
	while(scanf("%ld", &n)!=EOF && n!=0) {
		arr = malloc(sizeof(int)*n);
		hd = malloc(sizeof(long)*n);
		tl = malloc(sizeof(long)*n);
		for(i=0; i<n; i++)
			scanf("%d", arr+i);
		max_subsum(arr, n);
		printf("%ld\n", enumerate());
		free(tl);
		free(hd);
		free(arr);
	}
	return 0;
}

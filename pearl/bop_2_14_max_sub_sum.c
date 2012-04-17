/*
 * Problem:
 *     given you a sequence: a[1], a[2], a[3],..., a[n]
 *     find the maximum sum of a[i]+a[i+1]+...+a[j]
 *
 * POINT: DP
 * define: s[i] is the maxisum subsum ends with a[i], so
 * we get: s[i] = max(s[i-1]+a[i], a[i])
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define M 100
int arr[M];
int endwith[M];

int
find_subsum(int *arr, int size)
{
	int i, temp, max = 0;
	endwith[0] = arr[0];
	for(i=1; i<size; i++) {
		temp = endwith[i-1] + arr[i];
		endwith[i] = temp > arr[i] ? temp : arr[i];

		if(max < endwith[i])
			max = endwith[i];
	}
	return max;
}

int 
main(int argc, char **argv)
{
	int i, n;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", arr+i);

	printf("The maximum subsum is: %d\n", find_subsum(arr, n));
}

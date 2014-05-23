/*
 * Problem:
 *     Output all permutations of a given sequence
 */

#include<stdio.h>
#include<stdlib.h>

void 
swap(int *arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int count;

void
perm(int *arr, int k, int n) // perm arr[k..n]
{
	int i;
	if(k == n) {
		for(i=0; i<=n; i++)
			printf("%d\t", arr[i]);
		printf("\n");
		++count;
		return;
	} else {
		for(i=k; i<=n; i++) {
			swap(arr, i, k);
			perm(arr, k+1, n);
			swap(arr, k, i);
		}
	}
}

/* -------------------------test------------------------------ */
int
main(int argc, char *argv)
{
	int i, n, *arr;
	scanf("%d", &n);
	arr = malloc(n * sizeof(int));
	for(i=0; i<n; i++)
		scanf("%d", arr+i);

	count = 0;
	perm(arr, 0, n-1);
	printf("\nTotal: %d\n", count);

	return 0;
}

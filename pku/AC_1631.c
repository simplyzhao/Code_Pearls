/* O(nlogn) algorithm: the longest increasing sub-sequence [LIS] */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 40001
int num[MAX_LEN];
int aux[MAX_LEN];
int size, rt_len;

int
dp()
{
	int i, left, right, mid;
	rt_len = 1;
	aux[rt_len] = num[0];
	for(i=1; i<size; i++) {
		if(num[i] > aux[rt_len]) {
			++rt_len;
			aux[rt_len] = num[i];
		} else {
			/* binary search: O(logn) */
			left = 1;
			right = rt_len;
			while(left <= right) {
				mid = (left+right)/2;
				if(num[i]>aux[mid])
					left = mid+1;
				else
					right = mid-1;
			}
			aux[left] = num[i];
		}
	}
	return rt_len;
}

int
main(int argc, char **argv)
{
	int i, tests;
	scanf("%d", &tests);
	while(tests--) {
		scanf("%d", &size);
		for(i=0; i<size; i++)
			scanf("%d", num+i);
		printf("%d\n", dp());
	}
}

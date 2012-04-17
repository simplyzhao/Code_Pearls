/* LIS/LDS: nlogn */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 30001
int N, group[MAX_LEN];
int aux[MAX_LEN];

int
bin_search1(int *arr, int front, int rear, int target)
{
	int mid;
	while(front <= rear) {
		mid = (front+rear)/2;
		if(aux[mid] <= target)
			front = mid+1;
		else
			rear = mid-1;
	}
	return front;
}

int
bin_search2(int *arr, int front, int rear, int target)
{
	int mid;
	while(front <= rear) {
		mid = (front+rear)/2;
		if(aux[mid] >= target)
			front = mid+1;
		else
			rear = mid-1;
	}
	return front;
}

int
LIS() /* LUDS, maybe more accurate, meaning Longest Undecreasing Seq */
{
	int i, len = 1;
	aux[1] = group[0];
	for(i=1; i<N; i++) {
		if(group[i] >= aux[len]) {
			++len;
			aux[len] = group[i];
		} else {
			aux[bin_search1(aux, 1, len, group[i])] = group[i];
		}
	}
	return len;
}

int 
LDS() /* LUIS */
{
	int i, len=1;
	aux[1] = group[0];
	for(i=1; i<N; i++) {
		if(group[i] <= aux[len]) {
			++len;
			aux[len] = group[i];
		} else {
			aux[bin_search2(aux, 1, len, group[i])] = group[i];
		}
	}
	return len;
}

int
main(int argc, char **argv)
{
	int i, lis_len, lds_len; 
	while(scanf("%d", &N) != EOF) {
		for(i=0; i<N; i++)
			scanf("%d", group+i);
		lis_len = LIS();
		lds_len = LDS();
		printf("%d\n", N-(lis_len>lds_len ? lis_len : lds_len));
	}
}

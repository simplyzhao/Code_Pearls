#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* 给定一个有序数组arr, 求任意一个i使得arr[i]等于v, 不存在则返回-1 */
int
binary_search_1(int *arr, int begin, int end, int v)
{
	int mid;
	while(begin <= end) {
		mid = begin + ((end - begin)>>1);
		if(arr[mid] == v)
			return mid;
		else if(arr[mid] < v)
			begin = mid + 1;
		else 
			end = mid - 1;
	}
	return -1;
}

/* 给定一个有序数组arr, 求最小的i使得arr[i]等于v, 不存在则返回-1 */
int
binary_search_2(int *arr, int begin, int end, int v)
{
	int mid;
	int b = begin - 1;
	int e = end + 1;
	/* loop invariant: arr[b]<v && arr[e]>=v (assume arr[begin-1]<v, arr[end+1]>=v) */
	while(b < e-1) {
		mid = b + ((e - b)>>1);
		if(arr[mid] < v)
			b = mid;
		else
			e = mid;
	}
	if(e>end || arr[e]!=v)
		return -1;
	return e;
}

/* 给定一个有序数组arr, 求最大的i使得arr[i]等于v, 不存在则返回-1 */
int
binary_search_3(int *arr, int begin, int end, int v)
{
	int mid;
	int b = begin-1;
	int e = end+1;
	/* loop invariant: arr[b]<=v && arr[e]>v (assume arr[begin-1]<=v, arr[end+1]>v) */
	while(b < e-1) {
		mid = b + ((e - b)>>1);
		if(arr[mid] <= v)
			b = mid;
		else
			e = mid;
	}
	if(b<begin || arr[b]!=v)
		return -1;
	return b;
}

/* 给定一个有序数组arr, 求最大的i使得arr[i]小于v, 不存在则返回-1 */
int
binary_search_4(int *arr, int begin, int end, int v)
{
	int mid;
	int b = begin-1;
	int e = end+1;
	/* loop invariant: arr[b]<v && arr[v]>=v (assume arr[begin-1]<v, arr[end+1]>=v) */
	while(b < e-1) {
		mid = b + ((e - b)>>1);
		if(arr[mid] < v)
			b = mid;
		else
			e = mid;
	}
	if(b>=begin && arr[b]<v)
		return b;
	return -1;
}

/* 给定一个有序数组arr, 求最小的i使得arr[i]大于v, 不存在则返回-1 */
int
binary_search_5(int *arr, int begin, int end, int v)
{
	int mid;
	int b = begin - 1;
	int e = end + 1;
	/* loop invariant: arr[b]<=v && arr[e]>v (assume arr[begin-1]<=v, arr[end+1]>v) */
	while(b < e-1) {
		mid = b + ((e - b)>>1);
		if(arr[mid] <= v)
			b = mid;
		else
			e = mid;
	}
	if(e<=end && arr[e]>v)
		return e;
	return -1;
}

int
main(int argc, char **argv)
{
	int i, len, v, *arr;
	scanf("%d", &len);
	arr = (int *)malloc(sizeof(int) * len);
	for(i=0; i<len; ++i) 
		scanf("%d", arr+i);
	printf("\n\n");
	printf("Length: %d\n", len);
	for(i=0; i<len; ++i)
		printf("%d\t", arr[i]);
	printf("\nTEST TEST TEST\n");
	while(scanf("%d", &v) != EOF) {
		printf("binary_search_1: %d\n", binary_search_1(arr, 0, len-1, v));
		printf("binary_search_2: %d\n", binary_search_2(arr, 0, len-1, v));
		printf("binary_search_3: %d\n", binary_search_3(arr, 0, len-1, v));
		printf("binary_search_4: %d\n", binary_search_4(arr, 0, len-1, v));
		printf("binary_search_5: %d\n", binary_search_5(arr, 0, len-1, v));
	}
}

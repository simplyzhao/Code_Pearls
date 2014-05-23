#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101
/*
 * 给定一个固定长度的数组,将递增整数序列写入这个数组,当写到数组尾部时,返回数组开始重新写,并覆盖先前写过的数.
 * 请在这个特殊数组中找出给定的整数.
 */

int
binary_search(int *arr, int begin, int end, int target)
{
	if(begin > end)
		return -1;
	int mid = begin + ((end-begin)>>1);
	if(arr[mid] == target)
		return mid;
	else if(arr[mid] > target)
		return binary_search(arr, begin, mid-1, target);
	else
		return binary_search(arr, mid+1, end, target);
}

int
search_special(int *arr, int begin, int end, int target)
{
	if(begin > end)
		return -1;
	int rt, mid = begin + ((end-begin)>>1);
	if(arr[mid] == target)
		return mid;

	if(arr[mid] > arr[begin]) {
		if((rt=binary_search(arr, begin, mid-1, target)) != -1)
			return rt;
		return search_special(arr, mid+1, end, target);
	} else {
		if((rt=binary_search(arr, mid+1, end, target)) != -1)
			return rt;
		return search_special(arr, begin, mid-1, target);
	}
}

int
main(int argc, char **argv)
{
	int i, targ, len, array[MAX_LEN];
	printf("Length of Array: ");
	scanf("%d", &len);
	for(i=0; i<len; i++) {
		printf("Array[%d]=", i);
		scanf("%d", array+i);
	}
	while(scanf("%d", &targ) != EOF) 
		printf("Index of %d: %d\n", targ, search_special(array, 0, len-1, targ));

	return 0;
}

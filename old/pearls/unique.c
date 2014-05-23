/*
 * Problem:
 *  given an array which has already sorted, remove the duplicates
 *  like the 'unique' function in STL::<algorithm>
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Return: length of the array without duplicates */
int
unique(int *arr, int len)
{
	int i, j = 1;
	if(arr==NULL || len <= 1)
		return len;
	for(i=1; i<len; i++) {
		if(arr[i] != arr[i-1])
			arr[j++] = arr[i];
	}
	return j;
}

int
main(int argc, char **argv)
{
	int i, nlen;
	int data[] = {1, 2, 2, 3, 4, 5, 5, 5, 6, 7, 7};
	nlen = unique(data, sizeof(data)/sizeof(data[0]));
	for(i=0; i<nlen; i++)
		printf("%d\t", data[i]);
	printf("\n");
	return 0;
}

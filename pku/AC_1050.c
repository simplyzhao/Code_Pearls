/*
 * 最大子矩阵问题
 * 对于二维矩阵，可以合并其中一维，再利用最大子段和(O(n))求解
 * DP
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define M_R 100
#define M_C 100
int arr[M_R][M_C];
int row, col;

int
max_subsum(int *arr, int N)
{
	int i, t, max;
	max = t = arr[0];
	for(i=1; i<N; i++) {
		t = t+arr[i]>arr[i] ? t+arr[i] : arr[i];
		max = max>t ? max : t;
	}
	return max;
}

int 
enumerate()
{
	int t, max = 0;
	int i, j, k, len, temp[col];
	memset(temp, 0, sizeof(int)*col);
	for(len=1; len<=row; len++) {
		for(i=0; i<row; i++) {
			for(j=i; j<len; j++) {
				for(k=0; k<col; k++) {
					temp[k] += arr[j][k];
				}
			}
			t = max_subsum(temp, col);
			max = max>t ? max : t;
			memset(temp, 0, sizeof(int)*col);
		}
	}
	return max;
}

int
main(int argc, char **argv)
{
	int i, j;
	scanf("%d", &row);
	col = row; /* according to problem statement */
	for(i=0; i<row; i++)
		for(j=0; j<col; j++)
			scanf("%d", (*(arr+i))+j);

	printf("%d\n", enumerate());
	return 0;
}

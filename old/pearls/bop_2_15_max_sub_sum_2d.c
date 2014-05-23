/* 2D - maximum subsequence problem */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define WIDTH_MAX 101
#define HEIGHT_MAX 101
int width, height;
int matrix[HEIGHT_MAX][WIDTH_MAX];
int mtx_sum[HEIGHT_MAX][WIDTH_MAX];
int arr[HEIGHT_MAX], tmp[HEIGHT_MAX];

void
init()
{
	int i, j;
	scanf("%d %d", &height, &width); 
	for(i=1; i<=height; ++i)
		for(j=1; j<=width; ++j)
			scanf("%d", matrix[i]+j);

	for(i=0; i<=height; ++i)
		mtx_sum[i][0] = 0;
	for(j=0; j<=width; ++j)
		mtx_sum[0][j] = 0;
	for(i=1; i<=height; ++i)
		for(j=1; j<=width; ++j)
			mtx_sum[i][j] = mtx_sum[i-1][j] + mtx_sum[i][j-1] - mtx_sum[i-1][j-1] + matrix[i][j];
	printf("init() finished\n");
}

int
max_sub_sum_1d(int *arr, int begin, int end)
{
	int i, max;
	max = tmp[begin] = arr[begin];
	for(i=begin+1; i<=end; ++i) {
		tmp[i] = tmp[i-1]+arr[i] > arr[i] ? tmp[i-1]+arr[i] : arr[i];
		max = max < tmp[i] ? tmp[i] : max;
	}
	return max;
}

int
max_sub_sum_2d()
{
	int i, j, k, t, ret = INT_MIN;
	for(i=1; i<=width; ++i) {
		for(j=i; j<=width; ++j) {
			for(k=1; k<=height; ++k)
				arr[k] = mtx_sum[k][j] - mtx_sum[k][i-1] - mtx_sum[k-1][j] + mtx_sum[k-1][i-1];
			t = max_sub_sum_1d(arr, 1, height);
			ret = ret < t ? t : ret;
		}
	}
	return ret;
}

int
main(int argc, char **argv)
{
	init();
	printf("Ret: %d\n", max_sub_sum_2d());
}

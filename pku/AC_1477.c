#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 51
int arr[MAX_NUM];

int
main(int argc, char **argv)
{
	int i, n, sum, avg, total, tests=0;
	while(scanf("%d", &n)!=EOF && n!=0) {
		sum = total = 0;
		for(i=0; i<n; i++) {
			scanf("%d", arr+i);
			sum += arr[i];
		}
		avg = sum/n;
		for(i=0; i<n; i++)
			if(arr[i] > avg)
				total += (arr[i]-avg);
		printf("Set #%d\nThe minimum number of moves is %d.\n\n", ++tests, total);
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 101
#define MAX_LEN 5051 /* 1+2+3+...+100 */
int rows, num[MAX_LEN];
int table[MAX_N][MAX_N];

/* table[i][j] = max(table[i-1][j-1]+num[i][j], table[i-1][j]+num[i][j] */
int
dp()
{
	int i, j, k, tmp, max, rt;
	table[0][0] = num[0];
	for(i=1; i<rows; i++) {
		tmp = i*(i+1)/2;
		for(j=0; j<=i; j++) {
			max = 0;
			for(k=1; k>=0; k--) 
				if(j-k>=0 && j-k<=i-1) /* parent index: [i-1][j-k] */
					max = table[i-1][j-k]+num[tmp+j]>max ? table[i-1][j-k]+num[tmp+j] : max;
			table[i][j] = max;
		}
	}
	rt = 0;
	for(j=0; j<rows; j++)
		if(table[rows-1][j] > rt)
			rt = table[rows-1][j];
	return rt;
}

int
main(int argc, char **argv)
{
	int i, j, tmp;
	while(scanf("%d", &rows) != EOF) {
		for(i=0; i<rows; i++) {
			tmp = i*(i+1)/2;
			for(j=0; j<=i; j++) 
				scanf("%d", num+(tmp+j));
		}
		memset(table, 0, sizeof(table));
		printf("%d\n", dp());
	}
}

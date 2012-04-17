/*
 * Problem:
 *     given you an positive integer array, length 2N
 *     split the given array into two N length array: A, B, |sum(A)-sum(B)| should be minimal
 * 
 * See: BOP, Section 2.18, solution 2 & solution 3
 *
 * solution 3:
 *    f[i][v] indicates whether there exists [i] elements, their sum equals to [v]
 *    f[0][0] = true
 *    f[i][v] = true if f[i-1][v-array[k]] = true
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100
#define SUM_LIMIT 10000
int array[2*N+1];
int total, n, sum;
char table[N][SUM_LIMIT>>1];

void
init()
{
	int i;
	memset(table, 0, sizeof(table));
	sum = 0;
	scanf("%d", &total);
	n = total>>1;
	for(i=1; i<=total; ++i) {
		scanf("%d", array+i);
		sum += array[i];
	}
	sum >>= 1;
}

void
dp()
{
	int k, i, v;
	table[0][0] = 1;
	for(k=1; k<=total; ++k) {
		i = k<n ? k : n;
		for( ; i>=1; --i) {
			for(v=1; v<=sum; ++v) {
				if(v>=array[k] && table[i-1][v-array[k]] == 1)
					table[i][v] = 1;
			}
		}
	}
}

int
main(int argc, char **argv)
{
	init();
	dp();
	int v;
	for(v=sum; v>=0; --v)
		if(table[n][v] == 1) {
			printf("%d", v);
			break;
		}
}

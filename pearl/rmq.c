#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * RMQ: Range Minimum/Maximum Query 
 *
 * dp[i][j] represent the min/max value in range start with i, len 2^j
 *
 * dp[i][0] = a[i]
 * dp[i][j] = Min(dp[i][j-1], dp[i+2^(j-1)][j-1])
 */

#define MIN(a, b) (a)<(b) ? (a) : (b)
#define MAX(a, b) (a)>(b) ? (a) : (b)
#define MAX_NUM 50005
#define MAX_LEN_LOG 20

int num[MAX_NUM];
int dMin[MAX_NUM][MAX_LEN_LOG];
int dMax[MAX_NUM][MAX_LEN_LOG];
int len;

void
init_rmq()
{
	int i, j;
	for(i=0; i<len; i++) {
		dMin[i][0] = num[i];
		dMax[i][0] = num[i];
	}

	for(j=1; (1<<j)<=len; j++) {
		for(i=0; i+(1<<j)-1<len; i++) {
			dMin[i][j] = MIN(dMin[i][j-1], dMin[i+(1<<(j-1))][j-1]);
			dMax[i][j] = MAX(dMax[i][j-1], dMax[i+(1<<(j-1))][j-1]);
		}
	}
}

int
rmq(int begin, int end)
{
	int dis = end - begin + 1;
	int k;
	for(k=0; (1<<k)<dis; k++);
	if(k)
		--k;

	printf("MIN(dMin[%d][%d], dMin[%d][%d])\n", begin, k, end-(1<<k)+1, k);
	return MIN(dMin[begin][k], dMin[end-(1<<k)+1][k]);
}

/* FOR TEST ONLY */
void
print_rmq()
{
	int i, j;
	for(j=0; j<MAX_LEN_LOG; j++) {
		for(i=0; i<len; i++) 
			printf("%d ", dMin[i][j]);
		printf("\n");
	}
}

int
main(int argc, char **argv)
{
	int i;
	scanf("%d", &len);
	for(i=0; i<len; i++)
		scanf("%d", num+i);

	init_rmq();
	print_rmq();

	int b, e;
	while(scanf("%d %d", &b, &e) != EOF)
		printf("Result: %d\n", rmq(b, e));
}

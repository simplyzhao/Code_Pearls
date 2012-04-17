#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 1001
int N, points[MAX_LEN][MAX_LEN];
int result[MAX_LEN];

/* Attention: symmetrical */
void
solve()
{
	int i, j, k, count = 0;
	memset(points, 0, sizeof(points));
	for(i=1; i<MAX_LEN; i++) {
		for(j=0; j<i; j++) {
			if(!points[i][j])
				++count;
			for(k=1; i*k<MAX_LEN&&j*k<MAX_LEN; k++)
				points[i*k][j*k] = 1;
		}
		result[i] = count;
	}
}

int
main(int argc, char **argv)
{
	int i, tests;
	solve();
	scanf("%d", &tests);
	for(i=1; i<=tests; i++) {
		scanf("%d", &N);
		printf("%d %d %d\n", i, N, ((result[N]<<1)+1));
	}
}

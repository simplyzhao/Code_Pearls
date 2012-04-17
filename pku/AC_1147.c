#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 3001
int first_col[MAX_LEN], last_col[MAX_LEN];
int N, zeros, ones, next[MAX_LEN];

int
main(int argc, char **argv)
{
	int i, count;
	while(scanf("%d", &N) != EOF) {
		zeros = ones = 0;
		for(i=1; i<=N; i++) {
			scanf("%d", last_col+i);
			if(last_col[i] == 0)
				first_col[++zeros] = 0;
			else
				++ones;
		}
		for(i=1; i<=ones; i++)
			first_col[zeros+i] = 1;
		ones = zeros+1;
		zeros = 1;
		for(i=1; i<=N; i++) {
			if(last_col[i] == 0)
				next[zeros++] = i;
			else
				next[ones++] = i;
		}

		for(count=1, i=1; count<=N; i=next[i], ++count)
			printf("%d ", first_col[i]);
		printf("\n");
	}
}

/* DP */
/*
 * equation of state:
 * x[i] == y[j]
 *     table[i][j] = min(table[i-1][j-1](nothing), table[i-1][j]+1(deletion), table[i][j-1]+1(insertion))
 * x[i] != y[j]
 *     table[i][j] = min(table[i-1][j-1]+1(change), table[i-1][j]+1(deletion), table[i][j-1]+1(insertion))
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN 1001
#define min(a, b, c) ((a)>(b) ? ((b)>(c) ? (c) : (b)) : ((a)>(c) ? (c) : (a)))
char x[LEN], y[LEN];
int table[LEN][LEN];
int m, n;

int
dfs()
{
	int i, j;
	/* Attention: initialize */
	/* set table[i][0] and table[0][j] to INT_MAX, which caused WA */
	for(i=0; i<=m; i++)
		table[i][0] = i;
	for(j=0; j<=n; j++)
		table[0][j] = j;
	for(i=1; i<=m; i++) {
		for(j=1; j<=n; j++) {
			if(x[i-1] == y[j-1])
				table[i][j] = min(table[i-1][j-1], table[i-1][j]+1, table[i][j-1]+1);
			else
				table[i][j] = min(table[i-1][j-1], table[i-1][j], table[i][j-1]) + 1;
		}
	}
	return table[m][n];
}

int
main(int argc, char **argv)
{
	while(scanf("%d %s", &m, x) != EOF) {
		scanf("%d %s", &n, y);
		printf("%d\n", dfs());
	}
	return 0;
}

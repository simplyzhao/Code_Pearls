/* classic DP: LCS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN 300
#define max(a, b) ((a)>(b) ? (a) : (b))
char fst[LEN+1], snd[LEN+1];
int table[LEN+1][LEN+1];
int m, n;

int
dp_lcs()
{
	int i, j;
	for(i=0; i<=m; i++)
		table[i][0] = 0;
	for(j=0; j<=n; j++)
		table[0][j] = 0;

	for(i=1; i<=m; i++) {
		for(j=1; j<=n; j++) {
			if(fst[i-1] == snd[j-1])
				table[i][j] = table[i-1][j-1] + 1;
			else
				table[i][j] = max(table[i-1][j], table[i][j-1]);
		}
	}
	return table[m][n];
}

int
main(int argc, char **argv)
{
	while(scanf("%s %s", fst, snd) != EOF) {
		memset(table, 0, sizeof(table));
		m = strlen(fst);
		n = strlen(snd);
		printf("%d\n", dp_lcs());
	}

	return 0;
}

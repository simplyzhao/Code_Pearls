#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 10

char chessboard[MAX_LEN][MAX_LEN];
int record[MAX_LEN];
int n, k;
int total;

int
is_valid(int i, int depth)
{
	int j;
	for(j=0; j<depth; j++)
		if(record[j] == i)
			return 0;
	return 1;
}

void
dfs(int depth, int cur)
{
	int i, j;
	if(depth == n) {
		if(cur == k)
			++total;
		return;
	}
	if(cur+(n-depth) < k) /* pruning */
		return;
	for(i=0; i<n; i++) {
		if(chessboard[depth][i]=='#' && is_valid(i, depth)) {
			record[depth] = i;
			dfs(depth+1, cur+1);
			record[depth] = -1;
		}
	}
	dfs(depth+1, cur);
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %d", &n, &k)!=EOF) {
		if(n==-1 && k==-1)
			break;
		total = 0;
		memset(record, -1, sizeof(record));
		for(i=0; i<n; i++)
			scanf("%s", chessboard[i]);
		dfs(0, 0);
		printf("%d\n", total);
	}
	return 0;
}

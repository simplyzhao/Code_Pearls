#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_K 101
#define MAX_N 1001
#define MAX_M 10001

int k, n, m;
int paths[MAX_N][MAX_N];
int visited[MAX_N];
int starts[MAX_K];
int counts[MAX_N];

void
init()
{
	int i, j, p;
	memset(paths, 0, sizeof(paths));
	memset(starts, 0, sizeof(starts));
	memset(counts, 0, sizeof(counts));
	scanf("%d %d %d", &k, &n, &m);
	for(i=1; i<=k; i++)
		scanf("%d", starts+i);
	for(i=1; i<=m; i++) {
		scanf("%d %d", &j, &p);
		paths[j][p] = 1;
	}
}

void
solve(int index)
{
	int i;
	visited[index] = 1;
	++counts[index];
	for(i=1; i<=n; i++)
		if(paths[index][i] && !visited[i]) {
			solve(i);
		}
}

void
output()
{
	int i, total=0;
	for(i=1; i<=n; i++)
		if(counts[i] == k)
			++total;
	printf("%d\n", total);
}

int
main(int argc, char **argv)
{
	int i;
	init();
	for(i=1; i<=k; i++) {
		memset(visited, 0, sizeof(visited));
		solve(starts[i]);
	}
	output();
}

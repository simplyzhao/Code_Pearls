#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 31
#define MAX_NUM 27
char map[MAX_LEN][MAX_LEN];
int n, m;
int adj[MAX_NUM][MAX_NUM], num, in[MAX_NUM], visited[MAX_NUM];
int x1, y1, x2, y2;

void
search(char ch)
{
	int i, j;
	x1 = y1 = MAX_LEN;
	x2 = y2 = -1;
	for(i=0; i<n; i++)
		for(j=0; j<m; j++)
			if(map[i][j] == ch) {
				if(i<x1) x1 = i;
				if(i>x2) x2 = i;
				if(j<y1) y1 = j;
				if(j>y2) y2 = j;
			}
}

void
build_graph()
{
	int i, j, k;
	char ch;
	num = 0;
	memset(adj, 0, sizeof(adj));
	memset(in, -1, sizeof(in));
	for(i=0; i<n; i++) {
		for(j=0; j<m; j++) {
			if(map[i][j]=='.' || in[map[i][j]-'A']>-1)
				continue;
			in[map[i][j]-'A'] = 0;
			++num;
			search(map[i][j]);
			for(k=x1; k<=x2; k++) {
				ch = map[k][y1];
				if(ch != map[i][j])
					adj[map[i][j]-'A'][ch-'A'] = 1;
			}
			for(k=x1; k<=x2; k++) {
				ch = map[k][y2];
				if(ch != map[i][j])
					adj[map[i][j]-'A'][ch-'A'] = 1;
			}
			for(k=y1; k<=y2; k++) {
				ch = map[x1][k];
				if(ch != map[i][j])
					adj[map[i][j]-'A'][ch-'A'] = 1;
			}
			for(k=y1; k<=y2; k++) {
				ch = map[x2][k];
				if(ch != map[i][j])
					adj[map[i][j]-'A'][ch-'A'] = 1;
			}
		}
	}
	for(i=0; i<MAX_NUM; i++)
		for(j=0; j<MAX_NUM; j++)
			if(adj[i][j])
				++in[j]; /* in-degree */
}

void
topological_sort(char *str, int level)
{
	int i, j;
	if(level == num) {
		printf("%s\n", str);
		return;
	}
	for(i=0; i<MAX_NUM; i++) {
		if(in[i]==0 && !visited[i]) {
			str[level] = 'A'+i;
			visited[i] = 1;
			for(j=0; j<MAX_NUM; j++)
				if(adj[i][j])
					--in[j];
			topological_sort(str, level+1);
			visited[i] = 0;
			for(j=0; j<MAX_NUM; j++)
				if(adj[i][j])
					++in[j];
		}
	}
}

int
main(int argc, char **argv)
{
	int i;
	char str[MAX_NUM];
	while(scanf("%d %d", &n, &m)!=EOF) {
		for(i=0; i<n; i++)
			scanf("%s", map[i]);
		build_graph();
		memset(str, 0, sizeof(str));
		memset(visited, 0, sizeof(visited));
		topological_sort(str, 0);
	}
}

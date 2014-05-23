#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 29
#define INF 100000
int graph[MAX_NUM][MAX_NUM];
int color[MAX_NUM];
int num, ans;

void
init()
{
	int i, j, len;
	char conn[MAX_NUM];
	memset(graph, 0, sizeof(graph));
	memset(color, -1, sizeof(color));
	ans = INF;
	for(i=0; i<num; i++) {
		scanf("%s", conn);
		len = strlen(conn);
		for(j=2; j<len; j++)
			graph[i][conn[j]-'A'] = 1;
	}
}

int
is_valid(int depth, int cindex)
{
	int i;
	for(i=0; i<depth; i++)
		if(graph[depth][i] && color[i]==cindex)
			return 0;
	return 1;
}

void 
dfs(int depth, int used_colors)
{
	int i;
	if(used_colors >= ans) /* pruning */
		return;
	if(depth == num) {
		ans = used_colors<ans ? used_colors : ans;
		return;
	}
	for(i=1; i<=used_colors; i++) {
		if(is_valid(depth, i)) {
			color[depth] = i;
			dfs(depth+1, used_colors);
			color[depth] = -1;
		}
	}
	color[depth] = used_colors+1;
	dfs(depth+1, used_colors+1);
	color[depth] = -1;
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &num)!=EOF && num!=0) {
		init();
		dfs(0, 0);
		printf("%d %s\n", ans, ans<=1 ? "channel needed." : "channels needed.");
	}
	return 0;
}

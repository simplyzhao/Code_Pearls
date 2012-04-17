#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_REC 15

struct Rec {
	int uplft_x, uplft_y;
	int lwrgt_x, lwrgt_y;
	int color;
};
struct Rec recs[MAX_REC];
int n, visited[MAX_REC];
/* direction-graph can be presented by a two-dimensional array */
int degree[MAX_REC], graph[MAX_REC][MAX_REC];

/* if rec1 is immediate above rec2, return 1 */
int
is_immdt_above(struct Rec *rec1, struct Rec *rec2)
{
	if(rec1->lwrgt_x==rec2->uplft_x && !(rec1->lwrgt_y<=rec2->uplft_y || rec1->uplft_y>=rec2->lwrgt_y))
		return 1;
	return 0;
}

void
build_graph()
{
	int i, j;
	for(i=0; i<n; i++) 
		for(j=0; j<n; j++) 
			if(i!=j && is_immdt_above(recs+i, recs+j)) {
				graph[i][j] = 1;
				++degree[j];
			}
}

int
solve(int last_color, int count)
{
	int i, j, rt;
	int ans = 1000000;
	for(i=0; i<n; i++) {
		if(!visited[i] && degree[i]==0) {
			visited[i] = 1;
			if(recs[i].color != last_color)
				++count;
			for(j=0; j<n; j++)
				if(graph[i][j])
					--degree[j];
			rt = solve(recs[i].color, count);
			ans = rt<ans ? rt : ans;
			visited[i] = 0;
			if(recs[i].color != last_color)
				--count;
			for(j=0; j<n; j++)
				if(graph[i][j])
					++degree[j];
		}
	}
	if(ans == 1000000)
		ans = count;
	return ans;
}

int
main(int argc, char **argv)
{
	int i, tests;
	scanf("%d", &tests);
	while(tests--) {
		memset(visited, 0, sizeof(visited));
		memset(degree, 0, sizeof(degree));
		memset(graph, 0, sizeof(graph));
		scanf("%d", &n);
		for(i=0; i<n; i++)
			scanf("%d %d %d %d %d", &recs[i].uplft_x, &recs[i].uplft_y, &recs[i].lwrgt_x, &recs[i].lwrgt_y, &recs[i].color);
		build_graph();
		printf("%d\n", solve(-1, 0));
	}
	return 0;
}

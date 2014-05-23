#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 11
#define INF 0x7FFFFFFF
int N, m;
int min;
int mark[MAX_LEN];
struct Node {
	int dest;
	int adv;
	int p, r;
	struct Node *next;
};
struct Node *roads[MAX_LEN];
struct Node save[MAX_LEN];

void
init()
{
	int i, a, b, c, p, r, cnt = 0;
	min = INF;
	memset(mark, 0, sizeof(mark));
	memset(roads, 0, sizeof(roads));
	for(i=0; i<m; i++) {
		scanf("%d %d %d %d %d", &a, &b, &c, &p, &r);
		save[cnt].dest = b;
		save[cnt].adv = c;
		save[cnt].p = p;
		save[cnt].r = r;
		save[cnt].next = roads[a];
		roads[a] = save+cnt;
		++cnt;
	}
}

void
dfs(int from, int cur_cost)
{
	struct Node *node;
	if(cur_cost >= min || mark[from]>N)
		return;
	if(from == N) {
		min = cur_cost;
		return;
	}
	for(node=roads[from]; node!=NULL; node=node->next) {
		++mark[node->dest];
		dfs(node->dest, mark[node->adv]?cur_cost+node->p:cur_cost+node->r);
		--mark[node->dest];
	}
}

int
main(int argc, char **argv)
{
	while(scanf("%d %d", &N, &m)!=EOF) {
		init();
		mark[1] = 1;
		dfs(1, 0);
		if(min==INF)
			printf("impossible\n");
		else
			printf("%d\n", min);
	}
}

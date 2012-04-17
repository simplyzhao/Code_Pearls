#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_CITIES 101
#define INF 100000
struct Node {
	int dest;
	int len;
	int toll;
	struct Node *next;
};
struct Node roads[MAX_CITIES];
struct Node backup[MAX_CITIES*MAX_CITIES];
int visited[MAX_CITIES];
int k, n, r; 
int min_len;

void
dfs(int c, int cur_len, int cur_toll)
{
	int i;
	struct Node *node;
	if(cur_len>=min_len || cur_toll>k) 
		return;
	if(c == n) {
		min_len = cur_len;
		return;
	}
	for(node=roads[c].next; node!=NULL; node=node->next) {
		if(!visited[node->dest]) {
			visited[node->dest] = 1;
			dfs(node->dest, cur_len+node->len, cur_toll+node->toll);
			visited[node->dest] = 0;
		}
	}
}

int
main(int argc, char **argv)
{
	int i, s, d, l, t, cnt=0;
	memset(visited, 0, sizeof(visited));
	scanf("%d", &k);
	scanf("%d", &n);
	scanf("%d", &r);
	for(i=1; i<=n; i++)
		roads[i].next = NULL;
	for(i=0; i<r; i++) {
		scanf("%d %d %d %d", &s, &d, &l, &t);
		backup[cnt].dest = d;
		backup[cnt].len = l;
		backup[cnt].toll = t;
		backup[cnt].next = roads[s].next;
		roads[s].next = backup+cnt;
		++cnt;
	}
	min_len = INF;
	visited[1] = 1;
	dfs(1, 0, 0);
	if(min_len == INF)
		printf("-1\n");
	else
		printf("%d\n", min_len);
}

/* union-find sets, Kruskal algorithm */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 1001
#define MAX_M 15001
struct Edge{
	int len;
	int from, to;
}edges[MAX_M];
int parent[MAX_N], rank[MAX_N];
int n, m;

void
make_set()
{
	int i;
	for(i=1; i<=n; i++)
		parent[i] = i;
	memset(rank, 0, sizeof(rank));
}

int
find(int x)
{
	int tmp, rt = x;
	while(parent[rt] != rt)
		rt = parent[rt];
	while(x != rt) {
		tmp = parent[x];
		parent[x] = rt;
		x = tmp;
	}
	return rt;
}

void
Union(int x, int y)
{
	int a = find(x);
	int b = find(y);
	if(a == b)
		return;
	if(rank[a] > rank[b])
		parent[b] = a;
	else {
		parent[a] = b;
		if(rank[a] == rank[b])
			++rank[b];
	}
}

int
compare(const void *arg1, const void *arg2)
{
	return ((struct Edge *)arg1)->len - ((struct Edge *)arg2)->len;
}

void
init()
{
	int i;
	for(i=0; i<m; i++) 
		scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].len);
	qsort(edges, m, sizeof(struct Edge), compare);
}

void
kruskal()
{
	int i, a, b, count = 0;
	int mark[MAX_N];
	make_set();
	for(i=0; i<m; i++) {
		a = find(edges[i].from);
		b = find(edges[i].to);
		if(a != b) {
			mark[count++] = i;
			Union(a, b);
		}
	}
	/* output */
	printf("%d\n", edges[mark[count-1]].len);
	printf("%d\n", count);
	for(i=0; i<count; i++)
		printf("%d %d\n", edges[mark[i]].from, edges[mark[i]].to);
}

int
main(int argc, char **argv)
{
	while(scanf("%d %d", &n, &m) != EOF) {
		init();
		kruskal();
	}
}

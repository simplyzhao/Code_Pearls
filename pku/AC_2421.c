/* union-find sets, Kruskal algorithm */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 101
#define MAX_M (MAX_N*(MAX_N-1))>>1
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
	int i, j, tmp;
	m = 0;
	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++) {
			scanf("%d", &tmp);
			if(i<j && tmp) {
				edges[m].from = i;
				edges[m].to = j;
				edges[m++].len = tmp;
			}
		}
	qsort(edges, m, sizeof(struct Edge), compare);
	make_set();
	int q, f, t;
	scanf("%d", &q);
	for(i=0; i<q; i++) {
		scanf("%d %d", &f, &t);
		Union(f, t);
	}
}

void
kruskal()
{
	int i, a, b, count = 0;
    int sum = 0;
	for(i=0; i<m; i++) {
		a = find(edges[i].from);
		b = find(edges[i].to);
		if(a != b) {
			sum += edges[i].len;
			Union(edges[i].from, edges[i].to);
		}
	}
	/* output */
	printf("%d\n", sum);
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &n) != EOF) {
		init();
		kruskal();
	}
}

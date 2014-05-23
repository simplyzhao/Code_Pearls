/* Bellman-Ford algorithm */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 501
#define MAX_M 2501
#define MAX_W 201
#define INF 0x7FFFFFFF
struct Edge {
	int from, to;
	int cost;
} edges[MAX_M*2+MAX_W+MAX_N];
int d[MAX_N];
int n, total;

void
init()
{
	int i, m, w, f, t, c;
	scanf("%d %d %d", &n, &m, &w);
	total = 0; /* the number of edges */
	for(i=0; i<m; i++) {
		scanf("%d %d %d", &f, &t, &c);
		edges[total].from = f;
		edges[total].to = t;
		edges[total++].cost = c;
		edges[total].from = t;
		edges[total].to = f;
		edges[total++].cost = c;
	}
	for(i=0; i<w; i++) {
		scanf("%d %d %d", &f, &t, &c);
		edges[total].from = f;
		edges[total].to = t;
		edges[total++].cost = c*(-1);
	}
	/* in order to keep connectivity, add one vertex: '0' */
	for(i=1; i<=n; i++) {
		edges[total].from = 0;
		edges[total].to = i;
		edges[total++].cost = 0;
	}
}

void
relax(struct Edge *e)
{
	if(d[e->from] == INF)
		return;
	if(d[e->to] > d[e->from]+e->cost)
		d[e->to] = d[e->from]+e->cost;
}

int
bellman_ford()
{
	int i, j;
	for(i=0; i<=n; i++)
		d[i] = INF;
	d[0] = 0;
	for(i=0; i<n; i++)  /* n+1 vertices */
		for(j=0; j<total; j++)  /* 2*m+w+n edges */
			relax(edges+j);
	for(j=0; j<total; j++) {
		if(d[edges[j].to] > d[edges[j].from]+edges[j].cost)
			return 0;
	}
	return 1;
}

int
main(int argc, char **argv)
{
	int F;
	scanf("%d", &F);
	while(F--) {
		init();
		printf("%s\n", bellman_ford()==1?"NO":"YES");
	}
}

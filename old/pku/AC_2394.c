/* dijkstra algorithm */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_F 501
#define MAX_C 101
#define INF 0x7FFFFFFF
int adj[MAX_F][MAX_F];
int pos[MAX_C];
int in[MAX_F], d[MAX_F];
int f, p, c, m;

void
init()
{
	int i, from, to, cost;
	memset(adj, 0, sizeof(adj));
	scanf("%d %d %d %d", &f, &p, &c, &m);
	for(i=0; i<p; i++) {
		scanf("%d %d %d", &from, &to, &cost);
		if(adj[from][to]==0 || adj[from][to]>cost)
			adj[from][to] = adj[to][from] = cost;
	}
	for(i=1; i<=c; i++)
		scanf("%d", pos+i);
}

void
dijkstra()
{
	int i, j, k, cur;
	memset(in, 0, sizeof(in));
	for(i=1; i<=f; i++)
		d[i] = INF;
	d[1] = 0;
	in[1] = 1;
	for(j=1; j<=f; j++)
		if(!in[j] && adj[1][j])
			d[j] = adj[1][j];
	for(i=2; i<=f; i++) {
		cur = INF;
		for(j=1; j<=f; j++)
			if(!in[j] && d[j]<=cur) {
				k = j;
				cur = d[j];
			}
		in[k] = 1;
		for(j=1; j<=f; j++)
			if(!in[j] && adj[k][j] && d[k]!=INF)
				if(d[j] > d[k]+adj[k][j])
					d[j] = d[k]+adj[k][j];
	}
}

void
output()
{
	int i, n = 0;
	for(i=1; i<=c; i++)
		if(d[pos[i]] <= m) {
			++n;
			pos[i] = -1;
		}
	printf("%d\n", n);
	for(i=1; i<=c; i++)
		if(pos[i] == -1)
			printf("%d\n", i);
}

int
main(int argc, char **argv)
{
	init();
	dijkstra();
	output();
}

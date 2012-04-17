#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_E 50001
#define MAX_V 50002
#define INF 0x7FFFFFFF
struct Edge {
	int from, to;
	int cost;
}edges[MAX_E];
int n, min, max;
int d[MAX_V];

void
init()
{
	int i;
	min = INF;
	max = 0;
	for(i=1; i<=n; i++) {
		scanf("%d %d %d", &edges[i].to, &edges[i].from, &edges[i].cost);
		++edges[i].from;
		edges[i].cost *= (-1);
		if(edges[i].to<min)
			min = edges[i].to;
		if(edges[i].from>max)
			max = edges[i].from;
	}
}

void
bellman_ford()
{
	int i, j, flag;
	memset(d, 0, sizeof(d)); /* the same effect to 'super souce' in CLRS */
	for(i=min; i<=max; i++) { /* the number of verticles */
		flag = 1;
		/* RELAX each edge */
		for(j=1; j<=n; j++)
			if(d[edges[j].to] > d[edges[j].from]+edges[j].cost) {
				d[edges[j].to] = d[edges[j].from]+edges[j].cost;
				flag = 0;
			}
		for(j=min+1; j<=max; j++)
			if(d[j] > d[j-1]+1) {
				d[j] = d[j-1]+1;
				flag = 0;
			}
		for(j=max; j>min; j--)
			if(d[j-1] > d[j]) {
				d[j-1] = d[j];
				flag = 0;
			}
		if(flag)
			break;
	}
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &n) != EOF) {
		init();
		bellman_ford();
		printf("%d\n", d[max]-d[min]); /* d[max]=0 */
	}
}

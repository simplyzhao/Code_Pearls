/* 752K 79MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_V 301
#define MAX_P 31
#define INF 0x7FFFFFFF
int v, p;
int pos[MAX_V];
int cost[MAX_V][MAX_V];
int table[MAX_P][MAX_V];

void
init()
{
	int i, j, k, mid, diff;
	for(i=1; i<=v; i++) {
		for(j=i; j<=v; j++) {
			diff = 0;
			mid = (i+j)/2;
			for(k=i; k<=j; k++)
				diff += ((pos[k]>pos[mid])?(pos[k]-pos[mid]):(pos[mid]-pos[k]));
			cost[i][j] = cost[j][i] = diff;
		}
	}
}

int
dp()
{
	int i, j, k, min, tmp;
	memset(table, 0, sizeof(table));
	for(j=1; j<=v; j++)
		table[1][j] = cost[1][j];
	for(i=2; i<=p; i++) {
		for(j=i+1; j<=v; j++) {
			min = INF;
			for(k=i-1; k<=j-1; k++) {
				tmp = table[i-1][k] + cost[k+1][j];
				min = tmp<min ? tmp : min;
			}
			table[i][j] = min;
		}
	}
	return table[p][v];
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %d", &v, &p)!=EOF) {
		for(i=1; i<=v; i++)
			scanf("%d", pos+i);
		init();
		printf("%d\n", dp());
	}
}

/* Floyd-Warshall algorithm */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 101
#define INF 0x7FFFFFFF
#define Min(a,b) ((a)<(b) ? (a) : (b))
#define Max(a,b) ((a)<(b) ? (b) : (a))
int weight[MAX_N][MAX_N];
int d[MAX_N][MAX_N];
int max[MAX_N];
int n;

void
init()
{
	int i, j, cnt, t, c;
	memset(weight, 0, sizeof(weight));
	for(i=1; i<=n; i++) {
		scanf("%d", &cnt);
		for(j=0; j<cnt; j++) {
			scanf("%d %d", &t, &c);
			weight[i][t] = c;
		}
	}
}

void
floyd_warshall() /* O(n^3) */
{
	int i, j, k;
	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
			d[i][j] = (i==j?0:INF);
	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
			if(weight[i][j])
				d[i][j] = weight[i][j];
	for(k=1; k<=n; k++) {
		for(i=1; i<=n; i++) {
			for(j=1; j<=n; j++) {
				if(d[i][k]!=INF && d[k][j]!=INF)
					d[i][j] = Min(d[i][j], d[i][k]+d[k][j]);
			}
		}
	}
}

void
output()
{
	int i, j, p, rt;
	memset(max, 0, sizeof(max));
	rt = INF;
	for(i=1; i<=n; i++) {
		for(j=1; j<=n; j++)
			if(i!=j) {
				max[i] = Max(max[i], d[i][j]);
			}
		if(max[i] < rt) {
			rt = max[i];
			p = i;
		}
	}
	if(rt == INF)
		printf("disjoint\n");
	else
		printf("%d %d\n", p, rt);
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &n)!=EOF && n) {
		init();
		floyd_warshall();
		output();
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 3403
#define MAX_M 12881
#define max(a,b) ((a)>(b) ? (a) : (b))
int n, m;
/* MLE: int table[MAX_N][MAX_M]; */
int table[MAX_M];
int weight[MAX_N], rate[MAX_N];

void
dp()
{
	int i, j;
	memset(table, 0, sizeof(table));
	for(i=1; i<=n; i++)
		for(j=m; j>=weight[i]; j--) /* Attention: descent order */
			table[j] = max(table[j], table[j-weight[i]]+rate[i]);
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %d", &n, &m)!=EOF) {
		for(i=1; i<=n; i++)
			scanf("%d %d", weight+i, rate+i);
		dp();
		printf("%d\n", table[m]);
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_VOLUMN 100001
#define MAX_N 11
#define max(a,b) ((a)>(b) ? (a) : (b))
int vol, n;
int cv[MAX_N], num[MAX_N], f[MAX_VOLUMN];

/* f[i][v] = max(f[i-1][v], f[i-1][v-cost[i]]+value[i]) */
void
ZeroOnePack(int cost, int value)
{
	int v;
	for(v=vol; v>=cost; v--)
		f[v] = max(f[v], f[v-cost]+value);
}

/* f[i][v] = max(f[i-1][v], f[i][v-cost[i]]+value[i]) */
void
CompletePack(int cost, int value)
{
	int v;
	for(v=cost; v<=vol; v++)
		f[v] = max(f[v], f[v-cost]+value);
}

void
MultiplePack(int cost, int value, int amount)
{
	int k = 1;
	if(cost*amount >= vol)
		CompletePack(cost, value);
	else {
		while((amount-k) >= 0) {  
			ZeroOnePack(cost*k, value*k);
			amount -= k;
			k = k*2;
		}
		ZeroOnePack(cost*amount, value*amount);
	}
}

void
dp()
{
	int i;
	for(i=1; i<=n; i++)
		MultiplePack(cv[i], cv[i], num[i]);
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %d", &vol, &n)!=EOF) {
		memset(f, 0, sizeof(f));
		for(i=1; i<=n; i++)
			scanf("%d %d", num+i, cv+i);
		dp();
		printf("%d\n", f[vol]);
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101
#define INF 0x7FFFFFFF
#define min(a,b) ((a)<(b) ? (a) : (b))
int num[MAX_LEN], price[MAX_LEN];
int sum[MAX_LEN]; /* aux */
int table[MAX_LEN];
int c;

/*
 * f[i] represent the lowest possible price needed to buy list[1..i], so:
 *      f[i] = min (f[k] + (num[k+1]+...+num[i]+10)*price[i]), 0<=k<i-1
 */
int
dp()
{
	int i, k, tmp;
	sum[0] = 0;
	for(i=1; i<=c; i++)
		sum[i] = sum[i-1]+num[i];
	table[0] = 0;
	for(i=1; i<=c; i++) {
		table[i] = INF;
		for(k=0; k<=i-1; k++) {
			tmp = table[k] + (sum[i]-sum[k]+10)*price[i];
			table[i] = min(table[i], tmp);
		}
	}
	return table[c];
}

int
main(int argc, char **argv)
{
	int i, tests;
	scanf("%d", &tests);
	while(tests--) {
		scanf("%d", &c);
		for(i=1; i<=c; i++)
			scanf("%d %d", num+i, price+i);
		printf("%d\n", dp());
	}
}

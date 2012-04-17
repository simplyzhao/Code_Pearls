/* 32MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_F 101
#define MAX_V 101
#define INF 0xF0000000
int values[MAX_F][MAX_V];
int table[MAX_F][MAX_V];
int f, v;

/*
 * f[i][j] represent the maximum aesthetic values for putting the i(th) bunch 
 * in the j(th) vases(total i bunches), so:
 *      f[i][j] = max(f[i-1][k])+values[i][j], i-1<=k<j
 */
dp()
{
	int i, j, k, up, max, rt;
	for(j=1; j<=v-f+1; j++) 
		table[1][j] = values[1][j];
	for(i=2; i<=f; i++) {
		up = v-f+i;
		for(j=i; j<=up; j++) {
			max = INF;
			for(k=i-1; k<j; k++) 
				max = table[i-1][k] > max ? table[i-1][k] : max;
			table[i][j] = max+values[i][j];
		}
	}
	rt = INF;
	for(j=f; j<=v; j++)
		rt = table[f][j]>rt ? table[f][j] : rt;
	return rt;
}

int
main(int argc, char **argv)
{
	int i, j;
	while(scanf("%d %d", &f, &v)!=EOF) {
		for(i=1; i<=f; i++)
			for(j=1; j<=v; j++)
				scanf("%d", values[i]+j);
		printf("%d\n", dp());
	}
}

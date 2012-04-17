/* 63MS */
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
 * f[i][j] represent the maximum aesthetic values for putting the first [1..i]
 * bunches in the first [1..j] vases, so:
 *      f[i][j] = max (f[i-1][k] + tmp), i-1<=k<j
 */
dp()
{
	int i, j, k, p, t, up, tmp, max;
	table[1][1] = values[1][1];
	for(j=2; j<=v-f+1; j++) /* i = 1 */
		table[1][j] = values[1][j]>table[1][j-1] ? values[1][j] : table[1][j-1];
	for(i=2; i<=f; i++) {
		up = v-f+i;
		for(j=i; j<=up; j++) {
			max = INF;
			for(k=i-1; k<j; k++) {
				t = values[i][k+1];
				for(p=k+2; p<j; p++)
					t = values[i][p] > t ? values[i][p] : t;
				tmp = table[i-1][k] + t;
				max = tmp > max ? tmp : max;
			}
			table[i][j] = max;
		}
	}
	return table[f][v];
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

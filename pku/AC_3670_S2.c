#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 30001
#define INF 0x7FFFFFFF
#define Min(a, b) ((a) < (b) ? (a) : (b))
int N, group[MAX_LEN];
int ans, table[MAX_LEN][4];

void
dp()
{
	int i, j, k;
	/* Longest Undecrease Seq */
	/* F[i][j] represent the minimal changes needed for group[0..i] when
	 * changing group[i] to 'j', so: 
	 * F[i][j] = MIN(F[i-1][k])+1 1<=k<=j, when group[i]!=j
	 * F[i][j] = MIN(F[i-1][k]) 1<=k<=j, when group[i]==j */
	for(j=1; j<=3; j++) {
		if(group[0] == j)
			table[0][j] = 0;
		else
			table[0][j] = 1;
	}
	for(i=1; i<N; i++) {
		for(j=1; j<=3; j++) {
			table[i][j] = INF;
			for(k=1; k<=j; k++)
				table[i][j] = Min(table[i-1][k], table[i][j]);
			if(group[i] != j)
				++table[i][j];
			if(i == N-1)
				ans = Min(ans, table[i][j]);
		}
	}

	/* Longest Unincreasing Seq */
	/* F[i][j] = MIN(F[i-1][k])+1 j<=k<=3, when group[i]!=j
	 * F[i][j] = MIN(F[i-1][k]) j<=k<=3, when group[i]==j */
	for(j=1; j<=3; j++) {
		if(group[0] == j)
			table[0][j] = 0;
		else
			table[0][j] = 1;
	}
	for(i=1; i<N; i++) {
		for(j=1; j<=3; j++) {
			table[i][j] = INF;
			for(k=j; k<=3; k++)
				table[i][j] = Min(table[i-1][k], table[i][j]);
			if(group[i] != j)
				++table[i][j];
			if(i == N-1)
				ans = Min(ans, table[i][j]);
		}
	}
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d", &N) != EOF) {
		for(i=0; i<N; i++)
			scanf("%d", group+i);
		ans = INF;
		dp();
		printf("%d\n", ans);
	}
}

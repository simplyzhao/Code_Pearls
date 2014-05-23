#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 51
#define INF 9223372036854775807LL
#define maximal(a, b) ((a)>(b) ? (a) : (b))
#define minimal(a, b) ((a)<(b) ? (a) : (b))
char operand[MAX_LEN][2];
int operators[MAX_LEN];
int n, ans_len, ans[MAX_LEN];
long long int rt, max[MAX_LEN][MAX_LEN], min[MAX_LEN][MAX_LEN];

/*
 * when it comes to: '+'
 * max[i][j] = maximal(max[i][k] + max[k+1][j])
 * min[i][j] = minimal(min[i][k] + min[k+1][j])
 *
 * when it comes to: '*'
 * max[i][j] = maximal(max[i][k]*max[k+1][j], max[i][k]*min[k+1][j], min[i][k]*max[k+1][j], min[i][k]*min[k+1][j])
 * min[i][j] = minimal(max[i][k]*max[k+1][j], max[i][k]*min[k+1][j], min[i][k]*max[k+1][j], min[i][k]*min[k+1][j])
 *
 * i<=k<j
 */
void
solve(char *opd, int *ops, int del_edge)
{
	int i, j, k, len;
	for(i=1; i<=n; i++)
		max[i][i] = min[i][i] = ops[i];
	for(len=2; len<=n; len++) {
		for(i=1; i<=n-len+1; i++) {
			j = i+len-1;
			max[i][j] = -INF;
			min[i][j] = INF;
			for(k=i; k<j; k++) {
				if(opd[k] == 't') {
					max[i][j] = maximal(max[i][j], max[i][k]+max[k+1][j]);
					min[i][j] = minimal(min[i][j], min[i][k]+min[k+1][j]);
				} else { /* opd[k] == 'x' */
					max[i][j] = maximal(max[i][j], max[i][k]*max[k+1][j]);
					max[i][j] = maximal(max[i][j], max[i][k]*min[k+1][j]);
					max[i][j] = maximal(max[i][j], min[i][k]*max[k+1][j]);
					max[i][j] = maximal(max[i][j], min[i][k]*min[k+1][j]);

					min[i][j] = minimal(min[i][j], max[i][k]*max[k+1][j]);
					min[i][j] = minimal(min[i][j], max[i][k]*min[k+1][j]);
					min[i][j] = minimal(min[i][j], min[i][k]*max[k+1][j]);
					min[i][j] = minimal(min[i][j], min[i][k]*min[k+1][j]);
				}
			}
		}
	}
	if(max[1][n] >= rt) {
		if(max[1][n] == rt)
			ans[ans_len++] = del_edge;
		else {
			rt = max[1][n];
			ans_len = 0;
			ans[ans_len++] = del_edge;
		}
	}
}

int
main(int argc, char **argv)
{
	int i, j, k;
	char tmpopd[MAX_LEN];
	int tmpops[MAX_LEN];
	while(scanf("%d", &n) != EOF) {
		for(i=1; i<=n; i++)
			scanf("%s%d", operand[i], operators+i);
		rt = -INF;
		ans_len = 0;
		for(i=1; i<=n; i++) {
			for(j=i%n+1, k=1; j!=i; j=j%n+1, k++)
				tmpopd[k] = operand[j][0];
			tmpopd[k] = '\0';
			tmpops[1] = operators[i];
			for(j=i%n+1, k=2; j!=i; j=j%n+1, k++)
				tmpops[k] = operators[j];
			solve(tmpopd, tmpops, i);
		}
		printf("%lld\n", rt);
		for(i=0; i<ans_len; i++)
			printf("%d ", ans[i]);
		printf("\n");
	}
}

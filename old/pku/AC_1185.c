/* states compression DP (bitwise operation) */
/* see: states_compression.pdf written by: ZhouWei */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_M 11
#define MAX_N 101
#define maxsnum 65 /* maximum number solutions for a single line */
#define can_work(a, b) (((a) & (b)) == 0)
int n, m, ssnum; /* actual number of solutions for a single line */
int mask[MAX_N];
int s[maxsnum]; /* store the solutions for a single line */
int c[maxsnum]; /* store the number of 1-bits for each solution */
char artillery[MAX_N][MAX_M];
int f[MAX_N][maxsnum][maxsnum];

void 
dfs(int value, int depth, int bits)
{
	if(can_work(value, value<<2) && can_work(value, value>>2) && can_work(value, value<<1) && can_work(value, value>>1) && depth==m) {
		s[ssnum] = value;
		c[ssnum] = bits;
		++ssnum;
	}
	if(depth >= m)
		return;
	dfs(value, depth+1, bits);
	value = value|(1<<depth);
	dfs(value, depth+1, bits+1);
}

/*
 * maximum result for the i(th) line with s[j] and i-1(th) line with s[k]
 * f[i][j][k] = max(f[i-1][k][l]) + c[j]
 */
int
sc_dp()
{
	int i, j, k, l;
	/* Initialize */
	for(j=0; j<ssnum; j++)
		if(can_work(s[j], mask[0])) {
			for(k=0; k<ssnum; k++)
				f[0][j][k] = c[j];
		}
	for(i=1; i<n; i++) {
		for(j=0; j<ssnum; j++) {
			if(can_work(s[j], mask[i])) {
				for(k=0; k<ssnum; k++) {
					if(can_work(s[j], s[k]) && can_work(mask[i-1], s[k])) {
						for(l=0; l<ssnum; l++) {
							if(can_work(s[k], s[l]) && can_work(s[j], s[l]) && (i==1 || can_work(mask[i-2], s[l])))
								if(f[i-1][k][l]+c[j] > f[i][j][k])
									f[i][j][k] = f[i-1][k][l] + c[j];
						}
					}
				}
			}
		}
	}
	int rt = 0;
	for(j=0; j<ssnum; j++)
		for(k=0; k<ssnum; k++)
			rt = rt < f[n-1][j][k] ? f[n-1][j][k] : rt;
	return rt;
}

int
main(int argc, char **argv)
{
	int i, j;
	ssnum = 0;
	scanf("%d %d", &n, &m);
	memset(mask, 0, sizeof(mask));
	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));
	memset(f, 0, sizeof(f));
	getchar();
	for(i=0; i<n; i++) {
		for(j=0; j<m; j++) {
			scanf("%c", &artillery[i][j]);
			if(artillery[i][j] == 'H')
				mask[i] += (1<<(m-j-1));
		}
		getchar();
	}
	dfs(0, 0, 0);
	printf("%d\n", sc_dp());
	return 0;
}

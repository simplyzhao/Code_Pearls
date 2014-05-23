/* minimal minus & maximal plus */
/*
 * f[j][k]: solution for j persons, whose |D(J)-P(J)| = k, and has the maximal plus, so we have:
 *     f[j][k] = f[j-1][x], where x+(di-pi) = k, the j(th) person hasn't be chosen before 
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 201
#define MAX_M 21
#define MAX_GRADE 20
int n, m;
int pro[MAX_N], def[MAX_N];
int plus[MAX_N], minus[MAX_N];
int f[MAX_M][MAX_M*MAX_GRADE*2], sum[MAX_M][MAX_M*MAX_GRADE*2];
int rt[MAX_M];

int
compare(const void *arg1, const void *arg2)
{
	return (*(int *)arg1) - (*(int *)arg2);
}

void
dp()
{
	int i, j, k, p, q;
	int base = m*MAX_GRADE;
	memset(f, -1, sizeof(f));
	memset(sum, -1, sizeof(sum));
	/* initialize */
	for(i=1; i<=n; i++)
		if(sum[1][minus[i]+base] < plus[i]) {
			f[1][minus[i]+base] = i;
			sum[1][minus[i]+base] = plus[i];
		}
	for(j=2; j<=m; j++) {
		for(k=0; k<=2*m*MAX_GRADE; k++) {
			if(f[j-1][k] != -1) {
				for(i=1; i<=n; i++) {
					/* see if i has been used */
					q = k;
					for(p=j-1; p>=1; p--) {
						if(f[p][q] == i)
							break;
						q -= minus[f[p][q]];
					}
					if(p<1) {
						if(sum[j][k+minus[i]] < sum[j-1][k]+plus[i]) {
							f[j][k+minus[i]] = i;
							sum[j][k+minus[i]] = sum[j-1][k]+plus[i];
						}
					}
				}
			}
		}
	}
	int mm;
	for(i=0; i<=base; i++) {
		if(f[m][base-i]!=-1 || f[m][base+i]!=-1) {
			if(sum[m][base+i] > sum[m][base-i])
				mm = base+i;
			else
				mm = base-i;
			break;
		}
	}
	printf("Best jury has value %d for prosecution and value %d for defence:\n", (sum[m][mm]+(mm-base))/2, (sum[m][mm]-(mm-base))/2);

	for(j=m; j>=1; j--) {
		rt[j] = f[j][mm];
		mm -= minus[f[j][mm]];
	}

	qsort(rt+1, m, sizeof(int), compare);
	for(i=1; i<=m; i++)
		printf(" %d", rt[i]);
}

int
main(int argc, char **argv)
{
	int i, tc = 0;
	while(scanf("%d %d", &n, &m) != EOF) {
		if(n==0 && m==0)
			break;
		printf("Jury #%d\n", ++tc);
		for(i=1; i<=n; i++) {
			scanf("%d %d", pro+i, def+i);
			plus[i] = pro[i] + def[i];
			minus[i] = pro[i] - def[i];
		}
		/* dp */
		dp();
	}
	return 0;
}

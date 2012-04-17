/*
 * POINT: dfs & pruning
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NMAX 64
int n, sticks[NMAX], visited[NMAX];
int len, num; // len: stick length, num: number of sticks
int flag;

void
dfs(int depth, int sum, int cnt)
{
	int i, pre;
	if(cnt == num) {
		flag = 1;
	}
	else if(sum == len)
		dfs(0, 0, cnt+1);
	else {
		for(i=depth, pre=-1; i<n; i++) {
			if(sum+sticks[i]<=len && sticks[i]!=pre && !flag && !visited[i]) { /* pruning */
				visited[i] = 1;
				pre = sticks[i]; /* pruning: sticks of the same length don't need be searched more than once */
				dfs(i, sum+sticks[i], cnt);
				visited[i] = 0;
				if(sum==0) /* pruning: don't understand */
					return;
			}
		}
	}
	/*
	 * tail recursion --- could be removed by loop
	dfs(depth+1, sum, cnt);
	*/
}

int
compare(const void *fst, const void *sec)
{
	return *((int *)sec) - *((int *)fst);
}

int
main(int argc, char **argv)
{
	int i, max, sum;
	while(scanf("%d", &n)!=EOF && n!=0) {
		max = sum = 0;
		memset(sticks, 0, NMAX*sizeof(int));
		memset(visited, 0, NMAX*sizeof(int));
		for(i=0; i<n; i++) {
			scanf("%d", &sticks[i]);
			sum += sticks[i];
		}
		qsort(sticks, n, sizeof(int), compare);
		max = sticks[0];
		for(i=max; i<=sum; i++) {
			if(sum % i == 0) {
				len = i;
				num = sum / i;
				flag = 0;
				dfs(0, 0, 0);
				if(flag) {
					printf("%d\n", len);
					break;
				}
			}
		}
	}
	return 0;
}

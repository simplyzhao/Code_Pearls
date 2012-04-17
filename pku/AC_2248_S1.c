#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101
#define INF 0x7FFFFFFF
int num[MAX_LEN];
int ans[MAX_LEN];
int n, min;

int
dfs(int depth)
{
	int i, j;
	if(depth+1 >= min)
		return;
	if(num[depth] == n) {
		min = depth+1;
		memcpy(ans, num, min*sizeof(int));
		return;
	}
	for(i=depth; i>=0; i--) 
		if(num[i]+num[depth]<=n) {
			num[depth+1] = num[i] + num[depth];
			dfs(depth+1);
		}
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d", &n)!=EOF && n!=0) {
		min = INF;
		num[0] = 1;
		dfs(0);
		for(i=0; i<min; i++)
			printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}

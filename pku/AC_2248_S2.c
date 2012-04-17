/* Iterative deepening search (迭代加深搜索) */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101
int num[MAX_LEN];
int n, find, dplimit;

void
dfs(int depth)
{
	int i, j;
	if(depth >= dplimit)
		return;
	if(num[depth] == n) {
		if(!find) {
			for(j=0; j<=depth; j++)
				printf("%d ", num[j]);
			printf("\n");
			find = 1;
		}
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
	while(scanf("%d", &n)!=EOF && n!=0) {
		find = 0;
		num[0] = 1;
		for(dplimit=1; 1; dplimit++) {
			dfs(0);
			if(find)
				break;
		}
	}
}

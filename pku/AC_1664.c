#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n, m;
int total;

void
dfs(int level, int left, int last)
{
	int i, up;
	if(level==n) {
		if(left == 0)
			++total;
		return;
	}
	up = left<last ? left : last;
	for(i=up; i>=0; i--)
		dfs(level+1, left-i, i);
}

int
main(int argc, char **argv)
{
	int tests;
	scanf("%d", &tests);
	while(tests--) {
		scanf("%d %d", &m, &n);
		total = 0;
		dfs(0, m, m);
		printf("%d\n", total);
	}
}

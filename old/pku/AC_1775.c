/* Note: 10! = 3628800 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 10
int facs[MAX_LEN];
int mark, n;

void
init()
{
	int i, f = 1;
	facs[0] = 1;
	for(i=1; i<MAX_LEN; i++) {
		facs[i] = f*i;
		f = facs[i];
	}
}

void
dfs(int depth, int sum)
{
	if(sum == n) {
		mark = 1;
		return;
	}
	if(depth>=MAX_LEN || mark)
		return;
	dfs(depth+1, sum+facs[depth]);
	dfs(depth+1, sum);
}

int
main(int argc, char **argv)
{
	init();
	while(scanf("%d", &n)!=EOF && n>=0) {
		mark = 0;
		if(n > 0)
			dfs(0, 0);
		printf("%s\n", mark?"YES":"NO");
	}
}

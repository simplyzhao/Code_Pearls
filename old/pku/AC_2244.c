#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * f[1] = 0
 * f[i] = (f[i-1]+m)%i
 */
int
josephus(int n, int m)
{
	int i, s = 0;
	for(i=2; i<=n; i++) 
		s = (s+m)%i;
	return s+1;
}

int
main(int argc, char **argv)
{
	int n, m;
	while(scanf("%d", &n)!=EOF && n!=0) {
		m = 2;
		/* because first cut off city 1 and then begins every mth */
		while(josephus(n-1, m) != 1)
			++m;
		printf("%d\n", m);
	}
}

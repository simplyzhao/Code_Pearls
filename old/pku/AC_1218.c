#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101
int lock[MAX_LEN];
int n;

int
main(int argc, char **argv)
{
	int i, j, k, cnt, tests;
	scanf("%d", &tests);
	while(tests--) {
		cnt = 0;
		scanf("%d", &n);
		memset(lock, 0, sizeof(lock));
		for(i=1; i<=n; i++)
			lock[i] = (i%2==0 ? 1 : 0);
		for(j=3; j<=n; j++) {
			for(k=j; k<=n; k+=j)
				lock[k] = (lock[k]==1 ? 0 : 1);
		}
		for(i=1; i<=n; i++)
			if(!lock[i])
				++cnt;
		printf("%d\n", cnt);
	}
}

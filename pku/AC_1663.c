#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 10001
int pos[INF];

void
init()
{
	int i, cur=0;
	for(i=0; i<INF; i++) {
		pos[i] = cur;
		cur += (i%2==0?1:3);
	}
}

int
main(int argc, char **argv)
{
	int x, y, N;
	init();
	scanf("%d", &N);
	while(N--) {
		scanf("%d %d", &x, &y);
		if(x == y)
			printf("%d\n", pos[x]);
		else if(x == y+2)
			printf("%d\n", pos[y]+2);
		else
			printf("%s\n", "No Number");
	}
}

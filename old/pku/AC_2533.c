#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 1001
int num[MAX_LEN];
int max[MAX_LEN];
int len;

/*
 * f[i] represent the longest ascent sequence ended with num[i], so:
 *      f[i] = max ( f[j]+1, if num[j]<num[i], 0<=j<i)
 */
int
dp()
{
	int i, j, t, rt;
	max[0] = rt = 1;
	for(i=1; i<len; i++) {
		t = 1; /* WA twice here, for t=-1 */
		for(j=0; j<i; j++) {
			if(num[j] < num[i])
				t = max[j]+1>t ? max[j]+1 : t;
		}
		max[i] = t;
		rt = max[i]>rt ? max[i] : rt;
	}
	return rt;
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d", &len)!=EOF) {
		for(i=0; i<len; i++)
			scanf("%d", num+i);
		printf("%d\n", dp());
	}
}

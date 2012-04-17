#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 32767
int num[MAX_LEN];
int max[MAX_LEN];
int len;

/*
 * f[i] represent the longest descent sequence ended with num[i], so:
 *      f[i] = max ( f[j]+1, if num[j]>num[i], 0<=j<i)
 */
int
dp()
{
	int i, j, t, rt;
	max[0] = rt = 1;
	for(i=1; i<len; i++) {
		t = 1; /* WA twice here, for t=-1 */
		for(j=0; j<i; j++) {
			if(num[j] > num[i])
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
	int i, tmp, cnt = 0;
	while(scanf("%d", &tmp)!=EOF && tmp!=-1) {
		num[0] = tmp;
		len = 1;
		while(scanf("%d", num+len)!=EOF && num[len]!=-1)
			++len;
		printf("Test #%d:\n  maximum possible interceptions: %d\n\n", ++cnt, dp());
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 101
#define MAX_LEN 101
#define INF 0x7FFFFFFF
char str[MAX_NUM][MAX_LEN];
int n;
int idx, max;

int
find_substring()
{
	int i, j, k, len;
	char tmp[MAX_LEN], rtmp[MAX_LEN];
	for(len=max; len>0; len--) {
		for(i=0; i<=max-len; i++) {
			strncpy(tmp, str[idx]+i, len);
			for(j=0; j<len; j++)
				rtmp[j] = tmp[len-j-1]; 
			tmp[len] = rtmp[len] = '\0'; 
			for(k=0; k<n; k++) 
				if(strstr(str[k], tmp)==NULL && strstr(str[k], rtmp)==NULL)
					break;
			if(k==n)
				return len;
		}
	}
	return 0;
}

int
main(int argc, char **argv)
{
	int i, len, tests;
	scanf("%d", &tests);
	while(tests--) {
		scanf("%d", &n);
		max = INF;
		for(i=0; i<n; i++) {
			scanf("%s", str[i]);
			len = strlen(str[i]);
			if(len < max) {
				max = len;
				idx = i;
			}
		}
		printf("%d\n", find_substring());
	}
	return 0;
}

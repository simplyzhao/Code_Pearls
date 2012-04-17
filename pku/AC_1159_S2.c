#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 5001
char str[MAX_LEN];
int len;
short table[MAX_LEN][MAX_LEN];

short
dp()
{
	int i, j;
	/* if i>j, then table[i][j] = 0 */
	for(i=len-1; i>=1; i--) {
		for(j=i; j<=len; j++) {
			if(str[i] == str[j])
				table[i][j] = table[i+1][j-1];
			else
				table[i][j] = table[i+1][j]<table[i][j-1] ? table[i+1][j]+1 : table[i][j-1]+1;
		}
	}
	return table[1][len];
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &len) != EOF) {
		memset(table, 0, sizeof(table));
		scanf("%s", str+1);
		printf("%d\n", dp());
	}
}

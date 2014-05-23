#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 201
char first[MAX_LEN+1], second[MAX_LEN+1];
char final[MAX_LEN*2];
int flen, slen, tlen;
int table[MAX_LEN][MAX_LEN];

/* 
 * f[i][j] represent whether final[1..i+j] could be formed from first[1..i] and second[1..j]
 * f[i][j] is true if:
 *         a. final[i+j]==first[i] && f[i-1][j] is true, or
 *         b. final[i+j]==second[j] && f[i][j-1] is true
 */
int 
dp()
{
	int i, j, mark;
	mark = 1;
	for(i=1; i<=flen; i++) {
		if(first[i]==final[i] && mark)
			table[i][0] = 1;
		else {
			table[i][0] = 0;
			mark = 0;
		}
	}
	mark = 1;
	for(j=1; j<=slen; j++) {
		if(second[j]==final[j] && mark)
			table[0][j] = 1;
		else {
			table[0][j] = 0;
			mark = 0;
		}
	}
	for(i=1; i<=flen; i++) {
		for(j=1; j<=slen; j++) {
			if((final[i+j]==first[i]&&table[i-1][j]) || (final[i+j]==second[j]&&table[i][j-1]))
				table[i][j] = 1;
			else
				table[i][j] = 0;
		}
	}
	return table[flen][slen];
}

int
main(int argc, char **argv)
{
	int tests, cnt=0;
	scanf("%d", &tests);
	while(tests--) {
		scanf("%s %s %s", first+1, second+1, final+1);
		flen = strlen(first+1);
		slen = strlen(second+1);
		tlen = strlen(final+1);
		printf("Data set %d: %s\n", ++cnt, dp()?"yes":"no");
	}
}

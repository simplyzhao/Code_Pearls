#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 1000001
char str[MAX_LEN+1];
int len, next[MAX_LEN+1];

void
get_next() /* KMP preprocess */
{
	int i, j=0;
	next[1] = 0;
	for(i=2; i<=len; i++) {
		while(j && str[j+1]!=str[i])
			j = next[j];
		if(str[j+1] == str[i])
			++j;
		next[i] = j;
	}
}

int
main(int argc, char **argv)
{
	int i, tmp, tests=0;
	while(scanf("%d", &len)!=EOF && len) {
		scanf("%s", str+1);
		get_next();
		printf("Test case #%d\n", ++tests);
		for(i=2; i<=len; i++) {
			tmp = i - next[i];
			if(i%tmp==0 && i/tmp>1)
				printf("%d %d\n", i, i/tmp);
		}
		printf("\n");
	}
}

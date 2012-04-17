/* 860MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 1000003
char num[MAX_LEN], result[MAX_LEN];
int len;

void
solve()
{
	int i, mark, minus, tmp;
	minus = mark = 0;
	for(i=len-1; i>=0; i--) {
		minus += mark;
		if(minus <= (num[i]-'0')) {
			result[i] = num[i] - minus;
			mark = 0;
		} else {
			result[i] = num[i] + 10 - minus;
			mark = 1;
		}
		minus = result[i]-'0';
	}
	result[len] = '\0';
	if(result[0] == '0')
		printf("IMPOSSIBLE\n");
	else
		printf("%s\n", result);
}

int
main(int argc, char **argv)
{
	int tests = 0;
	while(scanf("%s", num)!=EOF && num[0]!='0') {
		len = strlen(num);
		printf("%d. ", ++tests);
		solve();
	}
}

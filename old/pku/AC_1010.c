/* 388K 547MS */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LEN 65 /* maximum number of different types of stamps */
#define UPPER 4 /* maximum number of stamps */
int types, stamps[MAX_LEN];
int request;
int maxdf, minusd, high, tie, exist, mark[MAX_LEN], ans[MAX_LEN];

int
compare(const void *arg1, const void *arg2)
{
	return (*(int *)arg1)-(*(int *)arg2);
}

void
output()
{
	int i, j;
	if(!exist) {
		printf("%d ---- none\n", request);
		return;
	}
	printf("%d (%d): ", request, maxdf);
	if(tie)
		printf("tie\n");
	else {
		for(i=0; i<types; i++) 
			for(j=0; j<ans[i]; j++)
				printf("%d ", stamps[i]);
		printf("\n");
	}
}

void
dfs(int remain, int index, int curdf, int curusd, int curhigh)
{
	int i, flag = 0;
	if(remain == 0) {
		if(curdf < maxdf)
			return;
		/* satisfy the conditions: UPDATE */
		if((curdf>maxdf) || (curdf==maxdf&&curusd<minusd) || (curdf==maxdf&&curusd==minusd&&curhigh>high)) {
			maxdf = curdf;
			minusd = curusd;
			high = curhigh;
			exist = 1;
			tie = 0; /* remember reset 'tie' */
			memcpy(ans, mark, sizeof(int)*MAX_LEN); /* copy the current best to 'ans' */
			return;
		}
		/* TIE occurred */
		if(curdf==maxdf && curusd==minusd && curhigh==high) {
			tie = 1;
			return;
		}
		return;
	}
	/* still exist several stamps unmarked */
	for(i=index; i<types; i++) { /* Attention: i starts from 'index', which avoid duplicates such as '1 3' and '3 1' */
		if(!mark[i] && stamps[i]<=remain && curusd+1<=UPPER) {
			++mark[i];
			flag = 1;
			dfs(remain-stamps[i], i+1, curdf+1, curusd+1, stamps[i]);
			--mark[i];
		}
	}
	/* all available stamps have been marked */
	if(!flag) {
		for(i=types-1; i>=0; i--) {
			if(stamps[i]<=remain && curusd+1<=UPPER) {
				++mark[i];
				dfs(remain-stamps[i], 0, curdf, curusd+1, curhigh);
				--mark[i];
			}
		}
	}
}

int
main(int argc, char **argv)
{
	while(1) {
		types = 0;
		if(scanf("%d", &stamps[types]) == EOF)
			break;
		++types;
		while(scanf("%d", &stamps[types]) && stamps[types])
			++types;
		qsort(stamps, types, sizeof(int), compare); /* ascent order */

		while(scanf("%d", &request) && request) { /* each request */
			maxdf = high = 0;
			minusd = MAX_LEN+1;
			exist = tie = 0;
			memset(mark, 0, sizeof(mark));
			dfs(request, 0, 0, 0, 0);
			output();
		}
	}
	return 0;
}

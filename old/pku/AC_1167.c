#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_R 910
#define MAX_T 60
#define MAX_RT 17
struct Route {
	int begin;
	int interval;
	int stops;
} routes[MAX_R];
int cnt, left, n, min, tm[MAX_T];

int 
compare(const void *arg1, const void *arg2)
{
	return ((struct Route *)arg2)->stops - ((struct Route *)arg1)->stops;
}

int
check(int begin, int interval)
{
	int i;
	for(i=begin; i<MAX_T; i+=interval)
		if(!tm[i])
			return 0;
	return 1;
}

void
init()
{
	int i, j, tmp;
	min = MAX_RT + 1;
	cnt = 0;
	left = n;
	memset(tm, 0, sizeof(tm));
	for(i=0; i<n; i++) {
		scanf("%d", &tmp);
		++tm[tmp];
	}
	for(i=0; i<29; i++) { /* 0<=begin<=29 */
		if(tm[i]) {
			for(j=i+1; j<59-i; j++) 
				if(check(i, j)) {
					routes[cnt].begin = i;
					routes[cnt].interval = j;
					routes[cnt++].stops = 1 + (59-i)/j;
				}
		}
	}
	qsort(routes, cnt, sizeof(struct Route), compare); /* descend order */
}

void
dfs(int index, int r_cnt)
{
	int i, k, j;
	if(left == 0) {
		min = min<r_cnt ? min : r_cnt;
		return;
	}
	for(i=index; i<cnt&&routes[i].stops>left; i++);
	for(k=i; k<cnt; k++) {
		/* important pruning */
		if(r_cnt+1+(left-routes[k].stops)/routes[k].stops >= min)
			return;

		if(check(routes[k].begin, routes[k].interval)) {
			for(j=routes[k].begin; j<MAX_T; j+=routes[k].interval) {
				--tm[j];
				--left;
			}
			dfs(k, r_cnt+1);
			for(j=routes[k].begin; j<MAX_T; j+=routes[k].interval) {
				++tm[j];
				++left;
			}
		}
	}
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &n) != EOF) {
		init();
		dfs(0, 0);
		printf("%d\n", min);
	}
}

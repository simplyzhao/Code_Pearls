#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 10001
#define Max(a,b) ((a)<(b)?(b):(a))
struct Prod {
	int profit;
	int deadline;
} prods[MAX_N];
int n, upper, value[MAX_N];

int
compare(const void *arg1, const void *arg2) /* ascend order: deadline */
{
	struct Prod *a = (struct Prod *)arg1;
	struct Prod *b = (struct Prod *)arg2;
	return a->deadline-b->deadline;
}

void
init()
{
	int i;
	for(i=0; i<n; i++)
		scanf("%d %d", &prods[i].profit, &prods[i].deadline);
	qsort(prods, n, sizeof(struct Prod), compare);
	upper = prods[n-1].deadline;
}

void
solve()
{
	int i, j;
	memset(value, 0, sizeof(value));
	for(i=0; i<n; i++) {
		for(j=prods[i].deadline; j>=1; j--) 
			value[j] = Max(value[j], value[j-1]+prods[i].profit);
		for(j=prods[i].deadline+1; j<=upper; j++)
			value[j] = Max(value[prods[i].deadline], value[j]);
	}
	printf("%d\n", value[upper]);
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &n) != EOF) {
		init();
		solve();
	}
}

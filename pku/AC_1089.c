#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 50001
struct Interval {
	int begin, end;
}itvs[MAX_LEN], target[MAX_LEN];
int N, total;

int
compare(const void *arg1, const void *arg2)
{
	struct Interval *a = (struct Interval *)arg1;
	struct Interval *b = (struct Interval *)arg2;
	if(a->begin == b->begin)
		return a->end - b->end;
	return a->begin - b->begin;
}

void
init()
{
	int i;
	for(i=0; i<N; i++)
		scanf("%d %d", &itvs[i].begin, &itvs[i].end);
	qsort(itvs, N, sizeof(struct Interval), compare);
	total = 0;
}

void
solve()
{
	int i;
	struct Interval cur = itvs[0];
	for(i=1; i<N; i++) {
		if(itvs[i].begin > cur.end) {
			target[total++] = cur;
			cur = itvs[i];
		} else {
			if(itvs[i].end > cur.end)
				cur.end = itvs[i].end;
		}
	}
	target[total++] = cur;
}

void
output()
{
	int i;
	for(i=0; i<total; i++)
		printf("%d %d\n", target[i].begin, target[i].end);
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &N) != EOF) {
		init();
		solve();
		output();
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 10001
struct Hotel {
	int dist;
	int cost;
} hotels[MAX_LEN];
int n;

int
compare(const void *arg1, const void *arg2)
{
	int diff = (((struct Hotel *)arg1)->dist - ((struct Hotel *)arg2)->dist);
	if(diff == 0)
		diff = (((struct Hotel *)arg1)->cost - ((struct Hotel *)arg2)->cost);
	return diff;
}

int
main(int argc, char **argv)
{
	int i, cur_min, cnt;
	while(scanf("%d", &n)!=EOF && n!=0) {
		for(i=0; i<n; i++)
			scanf("%d %d", &(hotels[i].dist), &(hotels[i].cost));
		qsort(hotels, n, sizeof(struct Hotel), compare);
		cnt = 1;
		cur_min = hotels[0].cost;
		for(i=1; i<n; i++) {
			if(hotels[i].cost >= cur_min)
				continue;
			else {
				++cnt;
				cur_min = hotels[i].cost;
			}
		}
		printf("%d\n", cnt);
	}
}

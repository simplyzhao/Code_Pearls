#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 50001
int n;
struct Point {
	int x, y;
}points[MAX_LEN];

int
compare(const void *arg1, const void *arg2)
{
	struct Point *a = (struct Point *)arg1;
	struct Point *b = (struct Point *)arg2;
	if(a->x == b->x)
		return a->y - b->y;
	return a->x - b->x;
}

int
main(int argc, char **argv)
{
	int i, j, cnt, ymax;
	while(scanf("%d", &n)!=EOF && n) {
		for(i=0; i<n; i++)
			scanf("%d %d", &points[i].x, &points[i].y);
		qsort(points, n, sizeof(struct Point), compare);
		/* O(n^2) AC 1600+MS 
		cnt = 0;
		for(i=0; i<n; i++) {
			for(j=i+1; j<n; j++) {
				if(points[j].y >= points[i].y)
					break;
			}
			if(j == n)
				++cnt;
		}
		*/
		/* O(nlgn) AC 235MS */
		cnt = 1;
		ymax = points[n-1].y;
		for(i=n-2; i>=0; i--) {
			if(ymax < points[i].y) {
				++cnt;
				ymax = points[i].y;
			}
		}
		printf("%d\n", cnt);
	}
}

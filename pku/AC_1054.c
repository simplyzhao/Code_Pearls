/* enumerate the first two points for each possible path */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 5001
#define is_valid(x, y) ((x)>0 && (x)<=R && (y)>0 && (y)<=C)
int R, C;
int total;
struct Point {
	int x, y;
} points[MAX_NUM];

/* from top to down, and left to right */
int
compare(const void *arg1, const void *arg2)
{
	struct Point *a = (struct Point *)arg1;
	struct Point *b = (struct Point *)arg2;
	if(a->x == b->x)
		return a->y - b->y;
	return a->x - b->x;
}

void
init()
{
	int i;
	scanf("%d", &total);
	for(i=0; i<total; i++)
		scanf("%d %d", &points[i].x, &points[i].y);
	qsort(points, total, sizeof(struct Point), compare);
}

void
solve()
{
	int i, j, tmp, max = 0;
	int diff_x, diff_y;
	struct Point p1, p2, next;
	struct Point *ptr;
	for(i=0; i<total; i++) {
		for(j=i+1; j<total; j++) {
			tmp = 2;
			p1 = points[i];
			p2 = points[j];
			diff_x = p2.x - p1.x;
			diff_y = p2.y - p1.y;
			if(is_valid(p1.x-diff_x, p1.y-diff_y)) /* starting outside */
				continue;
			if(!is_valid(p1.x+max*diff_x, p1.y+max*diff_y)) /* pruning */
				continue;
			next.x = p2.x + diff_x;
			next.y = p2.y + diff_y;
			while(is_valid(next.x, next.y)) {
				if((ptr=(struct Point *)bsearch(&next, points, total, sizeof(struct Point), compare)) == NULL) {
					tmp = 0; /* ending outside */
					break;
				}
				++tmp;
				next.x += diff_x;
				next.y += diff_y;
			}
			max = tmp>max ? tmp : max;
		}
	}
	printf("%d\n", max>2 ? max : 0);
}

int
main(int argc, char **argv)
{
	while(scanf("%d %d", &R, &C) != EOF) {
		init();
		solve();
	}
}

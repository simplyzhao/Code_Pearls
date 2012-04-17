/*
 * Problem:
 *     Ski
 *
 * Solution:
 *     first DFS, but it's gonna timeout
 *     so, let's DP(换个思路):
 *         某一路线: a->b->c:
 *         对于b来说, 最长路径可以是从c出发的最长路径加1
 *         而另一种思路是到达a的最长路径加1, 而且height(a)>height(b),
 *         因此可以将地图按高度从高到低排序, 再按此顺序依次求最长路径
 *
 * POINT: 动态规划
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 102
int row, col;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

struct Pnt {
	int x;
	int y;
	int height;
};
struct Pnt points[MAX*MAX];
int height[MAX*MAX];
int distance[MAX][MAX];

int
compare(const void *fst, const void *sec)
{
	if(((struct Pnt *)fst)->height > ((struct Pnt *)sec)->height)
		return -1;
	else
		return 1;
}

int can_go(int x, int y)
{
	return x>=0 && x<row && y>=0 && y<col;
}

int 
dp()
{
	int total = row*col;
	int i, j, x, y, sx, sy, td, max, longest=1;
	distance[points[0].x][points[0].y] = 1; //highest point
	for(i=1; i<total; i++) {
		max = 1; //max should be set 1, in case points[i] is a peek
		x = points[i].x;
		y = points[i].y;
		for(j=0; j<4; j++) { //four directions
			sx = x+dx[j];
			sy = y+dy[j];
			//points[sx*col+sy] is a higher point around points[i]
			if(can_go(sx, sy) && points[i].height<height[sx*col+sy]) { //distance[sx][sy]>0 indicates (sx, sy) a higher point
				td = distance[sx][sy]+1;
				max = max > td ? max : td;
			}
		}
		distance[x][y] = max;
		longest = longest > max ? longest : max;
	}
	return longest;
}

int
main(int argc, char **argv)
{
	int i, j, p;
	memset(points, 0, sizeof(struct Pnt)*MAX*MAX);
	memset(distance, 0, sizeof(int)*MAX*MAX);
	memset(height, 0, sizeof(int)*MAX*MAX);
	scanf("%d %d", &row, &col);
	for(i=0; i<row; i++)
		for(j=0; j<col; j++) {
			p = i*col+j;
			points[p].x = i;
			points[p].y = j;
			scanf("%d", &(points[p].height));
			height[p] = points[p].height;
		}
	qsort(points, row*col, sizeof(struct Pnt), compare); //sort

	printf("%d\n", dp());
}

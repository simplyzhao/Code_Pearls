/*
 * Problem(classic):
 *    there're many points in a plane surface, find the nearest two points
 *    see: <CLRS> 33.4 section
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define INF 0x7FFFFFFF
#define NUM_MAX 100000
#define THRESHOLD 3

struct Point {
	double x, y;
};
struct Point points[NUM_MAX];
int total, yindex[NUM_MAX];

double
min(double arg1, double arg2)
{
	return (arg1 <= arg2 ? arg1 : arg2);
}

double
distance(struct Point *arg1, struct Point *arg2)
{
	double x_diff = arg1->x - arg2->x;
	double y_diff = arg1->y - arg2->y;
	return sqrt(x_diff*x_diff + y_diff*y_diff);
}

int
compare_x(const void *arg1, const void *arg2)
{
	struct Point *p1 = (struct Point *)arg1;
	struct Point *p2 = (struct Point *)arg2;
	return (p1->x - p2->x);
}

int
compare_y(const void *arg1, const void *arg2)
{
	struct Point *p1 = points + *(int *)arg1;
	struct Point *p2 = points + *(int *)arg2;
	return (p1->y - p2->y);
}

void
init_preprocess()
{
	int i;
	scanf("%d", &total);
	for(i=0; i<total; ++i)
		scanf("%lf %lf", &points[i].x, &points[i].y);
	qsort(points, total, sizeof(struct Point), compare_x);
}

double
find_nearest(int begin, int end)
{
	int i, j;
	double ret = INF;
	if(end-begin+1 <= THRESHOLD) {
		for(i=begin; i<end; ++i) {
			for(j=i+1; j<=end; ++j)
				ret = min(ret, distance(points+i, points+j));
		}
		return ret;
	}
	int mid = begin + ((end - begin) >> 1);
	double dis = min(find_nearest(begin, mid), find_nearest(mid+1, end));
	int len = 0;
	for(j=mid; j>=begin && points[mid+1].x-points[j].x<=dis; --j)
		yindex[len++] = j;
	for(j=mid+1; j<=end && points[j].x-points[mid].x<=dis; ++j)
		yindex[len++] = j;
	qsort(yindex, len, sizeof(int), compare_y);
	ret = dis;
	for(i=0; i<=len-7; ++i) {
		for(j=i+1; j<=i+7; ++j)
			ret = min(ret, distance(points+yindex[i], points+yindex[j]));
	}
	return ret;
}

double
brute_force(int begin, int end)
{
	double ret = INF;
	int i, j;
	for(i=begin; i<end; ++i) {
		for(j=i+1; j<=end; ++j)
			ret = min(ret, distance(points+i, points+j));
	}
	return ret;
}

int
main(int argc, char **argv)
{
	init_preprocess();
	double ret = find_nearest(0, total-1);
	printf("\nNearest Distance[Brute Force]: %f\n", brute_force(0, total-1));
	printf("\nNearest Distance: %f\n", ret);
}

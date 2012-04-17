/* 
 * Data Structure: Segment Tree 
 * reference:
 * http://www.cppblog.com/Joe/archive/2010/09/15/126675.html
 * http://www.cppblog.com/Joe/archive/2010/09/15/126676.html
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100
#define LEFT(i) (i<<1)
#define RIGHT(i) ((i<<1)+1)
struct Node {
	int left, right;
	int n;
};
struct Node nodes[2*N+1]; /* array for tree, like heap */

void
build(int begin, int end, int step)
{
	int mid;
	nodes[step].left = begin;
	nodes[step].right = end;
	nodes[step].n = 0;
	if(begin == end)
		return;
	mid = (begin+end)>>1;
	build(begin, mid, LEFT(step));
	build(mid+1, end, RIGHT(step));
}

void
insert(int begin, int end, int step)
{
	int mid;
	if(nodes[step].left==begin && nodes[step].right==end) {
		++nodes[step].n;
		return;
	}
	mid = (nodes[step].left+nodes[step].right)>>1;
	if(mid<begin) {
		insert(begin, end, RIGHT(step));
	} else if(mid>=end) {
		insert(begin, end, LEFT(step));
	} else {
		insert(begin, mid, LEFT(step));
		insert(mid+1, end, RIGHT(step));
	}
}

void
calculate(int step, int target, int *rt)
{
	int begin, end, mid;
	begin = nodes[step].left;
	end = nodes[step].right;
	*rt = *rt + nodes[step].n;
	if(begin == end)
		return;
	mid = (begin+end)>>1;
	if(target <= mid)
		calculate(LEFT(step), target, rt);
	else if(target > mid)
		calculate(RIGHT(step), target, rt);
}

/*
int
main(int argc, char **argv)
{
	int count = 0;
	build(0, 7, 1);
	insert(2, 5, 1);
	insert(4, 6, 1);
	insert(0, 7, 1);
	calculate(1, 4, &count);
	printf("%d\n", count);
}

Output: 3
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 100001
#define MAX_T 31
#define LEFT(i) (i<<1)
#define RIGHT(i) ((i<<1)+1)
int L, T, O;
struct Node {
	int left, right;
	int color;
};
struct Node nodes[MAX_N*3];
int rt, visited[MAX_T];

void
build(int begin, int end, int step)
{
	int mid;
	nodes[step].left = begin;
	nodes[step].right = end;
	nodes[step].color = 1;
	if(begin == end)
		return;
	mid = (begin+end)>>1;
	build(begin, mid, LEFT(step));
	build(mid+1, end, RIGHT(step));
}

void
insert(int begin, int end, int color, int step)
{
	int mid;
	if(nodes[step].left==begin && nodes[step].right==end) {
		nodes[step].color = color;
		return;
	};
	if(nodes[step].color != -1) {
		nodes[LEFT(step)].color = nodes[RIGHT(step)].color = nodes[step].color;
		nodes[step].color = -1; /* mixed color */
	}
	mid = (nodes[step].left+nodes[step].right)>>1;
	if(begin > mid) 
		insert(begin, end, color, RIGHT(step));
	else if(end<=mid)
		insert(begin, end, color, LEFT(step));
	else {
		insert(begin, mid, color, LEFT(step));
		insert(mid+1, end, color, RIGHT(step));
	}
}

void
calculate(int begin, int end, int step)
{
	if(nodes[step].color != -1) {
		if(!visited[nodes[step].color]) {
			visited[nodes[step].color] = 1;
			++rt;
		}
		return;
	}
	int mid = (nodes[step].left+nodes[step].right)>>1;
	if(mid < begin)
		calculate(begin, end, RIGHT(step));
	else if(mid >= end)
		calculate(begin, end, LEFT(step));
	else {
		calculate(begin, mid, LEFT(step));
		calculate(mid+1, end, RIGHT(step));
	}
}

int
main(int argc, char **argv)
{
	int i, a, b, c;
	char ops[2];
	while(scanf("%d %d %d", &L, &T, &O) != EOF) {
		build(1, L, 1);
		for(i=1; i<=O; i++) {
			scanf("%s", ops);
			if(ops[0] == 'C') {
				scanf("%d %d %d", &a, &b, &c);
				if(a <= b)
					insert(a, b, c, 1);
				else
					insert(b, a, c, 1);
			} else if(ops[0] == 'P') {
				scanf("%d %d", &a, &b);
				rt = 0;
				memset(visited, 0, sizeof(visited));
				if(a <= b)
					calculate(a, b, 1);
				else
					calculate(b, a, 1);
				printf("%d\n", rt);
			}
		}
	}
}

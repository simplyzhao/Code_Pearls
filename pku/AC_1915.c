/* BFS, my first one */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CHESS_MAX 300
#define QUEUE 
int size;
int start_x, start_y;
int end_x, end_y;
int vstd_min[CHESS_MAX][CHESS_MAX];
struct Point {
	int x;
	int y;
};
int head, tail;
struct Point queue[100000];
const int dxy[][2] = {
	{-1, -2}, {-2, -1}, {1, -2}, {2, -1}, 
	{-1, 2}, {-2, 1}, {1, 2}, {2, 1}
}; 

int
is_valid(int i, int j)
{
	return (i>=0 && i<size && j>=0 && j<size);
}

int
bfs()
{
	int i, tx, ty, ttx, tty, cur;
	++tail;
	queue[tail].x = start_x;
	queue[tail].y = start_y;
	vstd_min[start_x][start_y] = 0;
	while(head < tail) {
		++head;
		tx = queue[head].x;
		ty = queue[head].y;
		cur = vstd_min[tx][ty];
		if(tx==end_x && ty==end_y)
			return cur;
		for(i=0; i<8; i++) {
			ttx = tx + dxy[i][0];
			tty = ty + dxy[i][1];
			if(is_valid(ttx, tty) && vstd_min[ttx][tty]==0) {
				++tail;
				queue[tail].x = ttx;
				queue[tail].y = tty;
				vstd_min[ttx][tty] = cur+1;
			}
		}
	}
	return 32767;
}

int
main(int argc, char **argv)
{
	int tests;
	scanf("%d", &tests);
	while(tests--) {
		memset(vstd_min, 0, sizeof(vstd_min));
		head = tail = -1;
		scanf("%d", &size);
		scanf("%d %d", &start_x, &start_y);
		scanf("%d %d", &end_x, &end_y);
		printf("%d\n", bfs());
	}
}

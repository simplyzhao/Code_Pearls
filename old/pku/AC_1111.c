#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 21
#define is_valid(x,y) (x>=0 && x<row && y>=0 && y<col)
const int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
struct Point {
	int x, y;
}queue[MAX_LEN*MAX_LEN];
char grid[MAX_LEN][MAX_LEN];
int visited[MAX_LEN][MAX_LEN];
int row, col, start_x, start_y;
int rt;

void
calculate(int x, int y)
{
	int i, tmpx, tmpy;
	for(i=0; i<4; i++) {
		tmpx = x + dx[i];
		tmpy = y + dy[i];
		if(!is_valid(tmpx, tmpy) || grid[tmpx][tmpy]=='.')
			++rt;
	}
}

void
bfs()
{
	int i, head, tail, nxt_x, nxt_y;
	head = -1;
	tail = 0;
	queue[tail].x = start_x-1;
	queue[tail].y = start_y-1;
	visited[start_x-1][start_y-1] = 1;
	while(head < tail) {
		++head;
		calculate(queue[head].x, queue[head].y);
		for(i=0; i<8; i++) {
			nxt_x = queue[head].x + dx[i];
			nxt_y = queue[head].y + dy[i];
			if(is_valid(nxt_x, nxt_y) && !visited[nxt_x][nxt_y] && grid[nxt_x][nxt_y]=='X') {
				++tail;
				queue[tail].x = nxt_x;
				queue[tail].y = nxt_y;
				visited[nxt_x][nxt_y] = 1;
			}
		}
	}
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %d %d %d", &row, &col, &start_x, &start_y) != EOF) {
		if(row==0 && col==0)
			break;
		for(i=0; i<row; i++)
			scanf("%s", grid[i]);
		rt = 0;
		memset(visited, 0, sizeof(visited));
		bfs();
		printf("%d\n", rt);
	}
}

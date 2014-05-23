/* BFS, totally by myself ^-^ */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE_MAX 77 /* 75+2 */
#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 8
char board[SIZE_MAX][SIZE_MAX];
int vstd_drt[SIZE_MAX][SIZE_MAX];
int width, height;
int start_x, start_y, end_x, end_y;
struct State {
	int x;
	int y;
	int min;
};
struct State queue[SIZE_MAX*SIZE_MAX];
int head, tail;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int 
is_valid(int x, int y)
{
	return (x>=0 && x<=height+1 && y>=0 && y<=width+1);
}

#define ADD(i, j, min, drt) ++tail; \
	queue[tail].x = i; \
    queue[tail].y = j; \
    queue[tail].min = min; \
    vstd_drt[i][j] = drt;

void
push_queue(int x, int y, int drt, int min)
{
	int i, j;
	switch(drt) {
		case UP:
			j = y;
			for(i=x; i>=0; i--) {
				if(board[i][j]=='X')
					break;
				if(!vstd_drt[i][j]) {
					ADD(i, j, min, drt);
				}
			}
			break;
		case DOWN:
			j = y;
			for(i=x; i<=height+1; i++) {
				if(board[i][j]=='X') 
					break;
			    if(!vstd_drt[i][j]) {
					ADD(i, j, min, drt);
				}
			}
			break;
		case LEFT:
			i = x;
			for(j=y; j>=0; j--) {
				if(board[i][j]=='X')
					break;
				if(!vstd_drt[i][j]) {
					ADD(i, j, min, drt);
				}
			}
			break;
		case RIGHT:
			i = x;
			for(j=y; j<=width+1; j++) {
				if(board[i][j]=='X')
					break;
				if(!vstd_drt[i][j]) {
					ADD(i, j, min, drt);
				}
			}
			break;
	}
}

int
bfs()
{
	int i, j, cur_x, cur_y, cur_min, nx, ny;
	for(i=0; i<4; i++) {
		nx = start_x + dx[i];
		ny = start_y + dy[i];
		if(is_valid(nx, ny) && board[nx][ny]==' ' && !vstd_drt[nx][ny])
			push_queue(nx, ny, 1<<i, 1);
	}
	while(head<tail) {
		++head;
		cur_x = queue[head].x;
		cur_y = queue[head].y;
		cur_min = queue[head].min;
		if(cur_x==end_x && cur_y==end_y)
			return cur_min;
		for(i=0; i<4; i++) {
			nx = cur_x + dx[i];
			ny = cur_y + dy[i];
			if(is_valid(nx, ny) && board[nx][ny]==' ' && !vstd_drt[nx][ny])
				push_queue(nx, ny, 1<<i, cur_min+1);
		}
	}
	return -1;
}

int
main(int argc, char **argv)
{
	int i, j, rt;
	int pair_num, board_num = 0;
	while(scanf("%d %d", &width, &height) && width != 0 && height != 0) {
		getchar();
		for(i=1; i<=height; i++) {
			for(j=1; j<=width; j++) {
				scanf("%c", &board[i][j]);
			}
			getchar();
		}
		for(j=0; j<width+2; j++)
			board[0][j] = board[height+1][j] = ' ';
		for(i=0; i<height+2; i++)
			board[i][0] = board[i][width+1] = ' ';
		printf("Board #%d:\n", ++board_num);
		pair_num = 0;
		while(scanf("%d %d %d %d", &start_y, &start_x, &end_y, &end_x)) {
			if(start_x==0 && start_y==0 && end_x==0 && end_y==0)
				break;
			head = -1;
			tail = -1;
			memset(vstd_drt, 0, sizeof(vstd_drt));
			printf("Pair %d: ", ++pair_num);
			board[end_x][end_y] = ' ';
			rt = bfs();
			if(rt==-1)
				printf("impossible.\n");
			else
				printf("%d segments.\n", rt);
			board[end_x][end_y] = 'X';
		}
		printf("\n");
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define is_valid(x, y) (x>=0 && x<row && y>=0 && y<col)
#define INF 100000
#define THROW_MAX 10
#define MAX_LEN 21
int row, col, start_x, start_y;
int board[MAX_LEN][MAX_LEN];
int min;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

void
dfs(int depth, int x, int y)
{
	int i, tx, ty;
	if(depth>=THROW_MAX || depth>=min) /* pruning */
		return;
	for(i=0; i<4; i++) {
		tx = x;
		ty = y;
		if(board[tx+dx[i]][ty+dy[i]] == 1) /* block immediately */
			continue;
		do {
			tx += dx[i];
			ty += dy[i];
			if(is_valid(tx, ty) && board[tx][ty] == 3) { /* end */
				min = depth+1;
				return;
			}
		} while(is_valid(tx, ty) && board[tx][ty]!=1);
		if(is_valid(tx, ty)) {
			board[tx][ty] = 0; /* the block disappears */
			dfs(depth+1, tx-dx[i], ty-dy[i]);
			board[tx][ty] = 1;
		}
	}
}

int
main(int argc, char **argv)
{
	int i, j;
	while(scanf("%d %d", &col, &row)!=EOF) {
		if(row==0 && col==0)
			break;
		min = INF;
		for(i=0; i<row; i++)
			for(j=0; j<col; j++) {
				scanf("%d", &board[i][j]);
				if(board[i][j] == 2) { /* start */
					start_x = i;
					start_y = j;
				}
			}
		dfs(0, start_x, start_y);
		if(min == INF)
			printf("%d\n", -1);
		else
			printf("%d\n", min);
	}
}

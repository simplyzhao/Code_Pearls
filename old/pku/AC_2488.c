#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 27
#define is_valid(x, y) (x>=0 && x<row && y>=0 && y<col)
struct Item {
	int x, y;
} path[MAX_LEN];
int visited[MAX_LEN][MAX_LEN];
int row, col, flag;
const int dx[] = {-1, 1, -2, 2, -2, 2, -1, 1};
const int dy[] = {-2, -2, -1, -1, 1, 1, 2, 2};

void
dfs(int depth, int x, int y)
{
	int i, tx, ty;
	visited[x][y] = 1;
	path[depth].x = x;
	path[depth].y = y;
	if(depth+1 == row*col) {
		if(!flag) {
			flag = 1;
			for(i=0; i<row*col; i++)
				printf("%c%d", 'A'+path[i].y, path[i].x+1);
			printf("\n");
		}
	}
	if(!flag) {
		for(i=0; i<8; i++) {
			tx = x + dx[i];
			ty = y + dy[i];
			if(is_valid(tx, ty) && !visited[tx][ty])
				dfs(depth+1, tx, ty);
		}
	}
	visited[x][y] = 0;
}

void
solve()
{
	int i, j;
	memset(visited, 0, sizeof(visited));
	flag = 0;
	for(i=0; i<row; i++)
		for(j=0; j<col; j++)
			if(!flag)
				dfs(0, i, j);
	if(!flag)
		printf("impossible\n");
}

int
main(int argc, char **argv)
{
	int i, tests;
	scanf("%d", &tests);
	for(i=1; i<=tests; i++) {
		scanf("%d %d", &row, &col);
		printf("Scenario #%d:\n", i);
		/* dfs */
		solve();
		printf("\n");
	}
}

/*
 * Problem:
 *     Ski
 *
 * Solution:
 *     first DFS, but it's gonna timeout
 *     so, let's 记忆化搜索:
 *         opt[i][j] = max{opt[i-1][j], opt[i+1][j], opt[i][j-1], opt[i][j+1]}+1
 * 
 * POINT: DFS+记忆化搜索
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100
int row, col;
int map[MAX][MAX];
int opt[MAX][MAX];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int
dp_memory(int x, int y)
{
	if(opt[x][y] != 0) //memory, simple but powerful
		return opt[x][y];

	int max = 0;
	int i, sx, sy, tmp;
	for(i=0; i<4; i++) { // four directions
		sx = x + dx[i];
		sy = y + dy[i];
		if(sx>=0 && sx<=row-1 && sy>=0 && sy<=col-1 && map[sx][sy]<map[x][y]) {
			tmp = dp_memory(sx, sy);
		    max = max > tmp ? max : tmp;
		}
	}
	opt[x][y] = max+1;
	return opt[x][y];
}

int
main(int argc, char **argv)
{
	int i, j, tmp, max=0;
	memset(map, 0, sizeof(int)*MAX*MAX);
	memset(opt, 0, sizeof(int)*MAX*MAX);
	scanf("%d %d", &row, &col);
	for(i=0; i<row; i++)
		for(j=0; j<col; j++)
			scanf("%d", (*(map+i)+j));

	for(i=0; i<row; i++)
		for(j=0; j<col; j++) {
			tmp = dp_memory(i, j);
			max = max > tmp ? max : tmp;
		}

	printf("%d\n", max);

	return 0;
}

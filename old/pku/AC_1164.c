/*
 * DFS
 * ^-^, totally by myself, and AC at the first time
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define WEST 1
#define NORTH 2
#define EAST 4
#define SOUTH 8
#define CAN_GO(sum, dir) (((15-(sum))&dir) != 0)
int dir[] = {WEST, NORTH, EAST, SOUTH};
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};
int row, col;
int castle[50][50];
int visited[50][50];
int total, largest;

int
is_valid(int i, int j)
{
	return (i>=0 && i<row && j>=0 && j<col);
}

void
solve()
{
	int i, j, temp;
	for(i=0; i<row; i++)
		for(j=0; j<col; j++)
			if(!visited[i][j]) {
				total += 1;
				temp = dfs(i, j);
				largest = temp > largest ? temp : largest;
			}
}

int
dfs(int i, int j)
{
	int k, sum, rooms = 1;
	visited[i][j] = 1;
	sum = castle[i][j];
	for(k=0; k<4; k++) {
		if(CAN_GO(sum, dir[k]) && is_valid(i+dx[k], j+dy[k]) && !visited[i+dx[k]][j+dy[k]]) {
			rooms += dfs(i+dx[k], j+dy[k]);
		}
	}
	return rooms;
}

int
main(int argc, char **argv)
{
	int i, j;
	while(scanf("%d %d", &row, &col) != EOF) {
		total = largest = 0;
		memset(visited, 0, sizeof(int)*50*50);
		for(i=0; i<row; i++)
			for(j=0; j<col; j++)
				scanf("%d", (*(castle+i))+j);
		solve();
		printf("%d\n%d\n", total, largest);
	}
	return 0;
}

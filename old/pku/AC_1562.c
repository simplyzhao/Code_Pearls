/*
 * DFS: 计算八连通域的个数
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define M 101
#define N 101
int m, n, count;
char map[M][N];
int visited[M][N];
const int dx[] = {1, -1, 0, 0, -1, 1, -1, 1};
const int dy[] = {0, 0, 1, -1, -1, -1, 1, 1};

int
within(int x, int y)
{
	return (x>=0 && x<m && y>=0 && y<n);
}

void
dfs(int x, int y)
{	
	int i, sx, sy;
	visited[x][y] = 1;
	for(i=0; i<8; i++) {
		sx = x+dx[i];
		sy = y+dy[i];
		if(within(sx, sy) && !visited[sx][sy] && map[sx][sy]=='@')
			dfs(sx, sy);
	}
}
	
void
solve()
{
	int i, j;
	for(i=0; i<m; i++)
		for(j=0; j<n; j++) 
			if(map[i][j] == '@' && !visited[i][j]) {
				dfs(i, j);
				count+=1;
			}
}

int 
main(int argc, char **argv)
{
	int i, j, c;
	while(scanf("%d %d", &m, &n)!=EOF && m!=0) {
		count = 0;
		memset(map, 0, sizeof(char)*M*N);
		memset(visited, 0, sizeof(int)*M*N);
		for(i=0; i<m; i++) 
				scanf("%s", map[i]); //汗...之前用"%c"进行输入，一直WA
		solve();
		printf("%d\n", count);
		getchar();
	}
	return 0;
}

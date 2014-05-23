#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_W 83
#define MAX_H 1001
#define is_valid(x,y) (x>=0 && x<H && y>=0 && y<W)
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
char photo[MAX_H][MAX_W];
int hash[MAX_H][MAX_W];
int W, H;

int
dfs(int x, int y)
{
	int i, nx, ny, rt = 1;
	hash[x][y] = 1;
	for(i=0; i<4; i++) {
		nx = x+dx[i];
		ny = y+dy[i];
		if(is_valid(nx, ny) && photo[nx][ny]=='*' && !hash[nx][ny]) 
			rt += dfs(nx, ny);
	}
	return rt;
}

int
solve()
{
	int i, j, tmp, value = -1;
	for(i=0; i<H; i++)
		for(j=0; j<W; j++) {
			if(photo[i][j]=='*' && !hash[i][j]) {
				tmp = dfs(i, j);
				value = tmp > value ? tmp : value;
			}
		}
	return value;
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %d", &W, &H) != EOF) {
		for(i=0; i<H; i++)
			scanf("%s", photo[i]);
		memset(hash, 0, sizeof(hash));
		printf("%d\n", solve());
	}
}

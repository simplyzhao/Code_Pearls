#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 21
#define is_valid(x, y) (x>=0&&x<R&&y>=0&&y<C)
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
int R, C;
int rt, hash[26]; /* A-Z */
char map[MAX_LEN][MAX_LEN];

void
dfs(int x, int y, int cur)
{
	int i, mark, next_x, next_y;
	mark = 0;
	hash[map[x][y]] = 1;
	for(i=0; i<4; i++) {
		next_x = x + dx[i];
		next_y = y + dy[i];
		if(is_valid(next_x, next_y) && !hash[map[next_x][next_y]]) {
			mark = 1;
			hash[map[next_x][next_y]] = 1;
			dfs(next_x, next_y, cur+1);
			hash[map[next_x][next_y]] = 0;
		}
	}
	if(!mark)
		rt = cur>rt ? cur : rt;
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %d", &R, &C) != EOF) {
		for(i=0; i<R; i++)
			scanf("%s", map[i]);
		rt = -1;
		memset(hash, 0, sizeof(hash));
		dfs(0, 0, 1);
		printf("%d\n", rt);
	}
}

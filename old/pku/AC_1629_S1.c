#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 11
#define MAX_WORDS 101
#define is_valid(x, y) (x>=0 && x<n && y>=0 && y<m)
char grid[MAX_LEN][MAX_LEN];
char words[MAX_WORDS][MAX_WORDS];
char ans[MAX_WORDS];
int words_len[MAX_WORDS];
int visited[MAX_LEN][MAX_LEN];
int n, m, p;
/* up, down, left, right */
const dx[] = {-1, 1, 0, 0};
const dy[] = {0, 0, -1, 1};
void solve(int);

void
init()
{
	int i;
	memset(visited, 0, sizeof(visited));
	scanf("%d %d %d", &n, &m, &p);
	for(i=0; i<n; i++)
		scanf("%s", grid[i]);
	for(i=0; i<p; i++) {
		scanf("%s", words[i]);
		words_len[i] = strlen(words[i]);
	}
}

int
compare(const void *arg1, const void *arg2)
{
	return *((char *)arg1) - *((char *)arg2);
}

void
output()
{
	int i, j, count=0;
	for(i=0; i<n; i++)
		for(j=0; j<m; j++)
			if(visited[i][j] == 0)
				ans[count++] = grid[i][j];
	qsort(ans, count, sizeof(char), compare);
	for(i=0; i<count; i++)
		printf("%c", ans[i]);
	printf("\n");
	exit(0);
}

void
set(int x, int y, int index, int ct)
{
	int i, tx, ty;
	//printf("(%d, %d)\n", x, y);
	visited[x][y] = index+1;
	if(ct+1 == words_len[index]) {
		solve(index+1);
		visited[x][y] = 0;
		return;
	}
	for(i=0; i<4; i++) {
		tx = x + dx[i];
		ty = y + dy[i];
		if(is_valid(tx, ty) && !visited[tx][ty] && grid[tx][ty]==words[index][ct+1])
			set(tx, ty, index, ct+1);
	}
	visited[x][y] = 0;
}

void
solve(int index)
{
	int i, j;
	if(index == p) {
		/*
		 * remove this comment and 'output', 
		 * then this code can present all the possible solutions
		for(i=0; i<n; i++) {
			for(j=0; j<m; j++) {
				printf("%d\t", visited[i][j]);
			}
			printf("\n");
		}
		return;
		*/
		output();
	}
	char c = words[index][0];
	for(i=0; i<n; i++) {
		for(j=0; j<m; j++) {
			if(grid[i][j]==c && !visited[i][j])
				set(i, j, index, 0);
		}
	}
}

int
main(int argc, char **argv)
{
	init();
	solve(0);
}

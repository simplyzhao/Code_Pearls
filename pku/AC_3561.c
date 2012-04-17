#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101
#define is_valid(x, y) ((x)>=0 && (x)<N && (y)>=0 && (y)<M)
int N, M;
char image[MAX_LEN][MAX_LEN];
int visited[MAX_LEN][MAX_LEN];
int hor, vert, diag;

void
mark(int i, int j, int dx, int dy, char ch)
{
	while(is_valid(i+dx, j+dy) && image[i+dx][j+dy]==ch) {
		visited[i+dx][j+dy] = 1;
		i += dx;
		j += dy;
	}
}

void
solve()
{
	int i, j;
	char ch;
	for(i=0; i<N; i++) {
		for(j=0; j<M; j++) {
			ch = image[i][j];
			if(ch!='.' && !visited[i][j]) {
				visited[i][j] = 1;
				switch(ch) {
					case '-':
						++hor;
						mark(i, j, 0, -1, ch);
						mark(i, j, 0, 1, ch);
						break;
					case '|':
						++vert;
						mark(i, j, -1, 0, ch);
						mark(i, j, 1, 0, ch);
						break;
					case '\\':
						++diag;
						mark(i, j, 1, 1, ch);
						mark(i, j, -1, -1, ch);
						break;
					case '/':
						++diag;
						mark(i, j, 1, -1, ch);
						mark(i, j, -1, 1, ch);
						break;
				}
			}
		}
	}
}

int
main(int argc, char **argv)
{
	int i, tests;
	scanf("%d", &tests);
	while(tests--) {
		scanf("%d %d", &N, &M);
		for(i=0; i<N; i++)
			scanf("%s", image[i]);
		memset(visited, 0, sizeof(visited));
		hor = vert = diag = 0;
		solve();
		if(hor+vert+diag == 1)
			printf("CORRECT\n");
		else
			printf("INCORRECT\n");
	}
}

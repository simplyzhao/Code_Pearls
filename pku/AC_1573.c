#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 12
#define is_valid(x, y) (x>=0 && x<R && y>=0 && y<C)
char map[MAX_LEN][MAX_LEN];
int steps[MAX_LEN][MAX_LEN];
int R, C, entry;

void
solve()
{
	char ch;
	int cx, cy, px, py;
	cx = px = 0;
	cy = py = entry-1;
	while(is_valid(cx, cy) && !steps[cx][cy]) {
		steps[cx][cy] = steps[px][py] + 1;
		ch = map[cx][cy];
		px = cx;
		py = cy;
		switch(ch) {
			case 'N':
				cx = px-1;
				cy = py;
				break;
			case 'S':
				cx = px+1;
				cy = py;
				break;
			case 'W':
				cx = px;
				cy = py-1;
				break;
			case 'E':
				cx = px;
				cy = py+1;
				break;
		}
	}
	if(!is_valid(cx, cy))
		printf("%d step(s) to exit\n", steps[px][py]);
	else if(steps[cx][cy])
		printf("%d step(s) before a loop of %d step(s)\n", steps[cx][cy]-1, steps[px][py]-steps[cx][cy]+1);
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %d %d", &R, &C, &entry)!=EOF && R) {
		for(i=0; i<R; i++)
			scanf("%s", map[i]);
		memset(steps, 0, sizeof(steps));
		solve();
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 31
#define QUEUE_SIZE 100000
#define is_valid(l, r, c) (l>=0 && l<level && r>=0 && r<row && c>=0 && c<column)
char maze[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int level, row, column;
int begin_l, begin_r, begin_c;
int end_l, end_r, end_c;
/* direction: north, south, west, east, up, down */
const int dl[] = {0, 0, 0, 0, -1, 1};
const int dr[] = {-1, 1, 0, 0, 0, 0};
const int dc[] = {0, 0, -1, 1, 0, 0};
struct EACH {
	int l, r, c;
	int mins;
} queue[QUEUE_SIZE];
int head, tail;


void
init()
{
	int i, j;
	char *p;
	memset(visited, 0, sizeof(visited));
	memset(queue, 0, sizeof(queue));
	head = -1;
	tail = 0;
	for(i=0; i<level; i++) {
		for(j=0; j<row; j++) {
			scanf("%s", maze[i][j]);
			if((p=strchr(maze[i][j], 'S')) != NULL) {
				begin_l = i;
				begin_r = j;
				begin_c = p-maze[i][j];
			}
			if((p=strchr(maze[i][j], 'E')) != NULL) {
				end_l = i;
				end_r = j;
				end_c = p-maze[i][j];
			}
		}
		getchar();
	}
}

int
bfs()
{
	int i, tl, tr, tc, cl, cr, cc, cm;
	queue[tail].l = begin_l;
	queue[tail].r = begin_r;
	queue[tail].c = begin_c;
	queue[tail].mins = 0;
	visited[begin_l][begin_r][begin_c] = 1;
	while(head < tail) {
		++head;
		cl = queue[head].l;
		cr = queue[head].r;
		cc = queue[head].c;
		cm = queue[head].mins;
		if(cl==end_l && cr==end_r && cc==end_c)
			return cm;
		for(i=0; i<6; i++) {
			tl = cl + dl[i];
			tr = cr + dr[i];
			tc = cc + dc[i];
			if(is_valid(tl, tr, tc) && !visited[tl][tr][tc] && maze[tl][tr][tc]!='#') {
				visited[tl][tr][tc] = 1;
				++tail;
				queue[tail].l = tl;
				queue[tail].r = tr;
				queue[tail].c = tc;
				queue[tail].mins = cm+1;
			}
		}
	}
	return -1;
}

int
main(int argc, char **argv)
{
	int m;
	while(scanf("%d %d %d", &level, &row, &column) != EOF) {
		if(level == 0)
			break;
		init();
		m = bfs();
		if(m == -1)
			printf("Trapped!\n");
		else
			printf("Escaped in %d minute(s).\n", m);
		getchar();
	}
}

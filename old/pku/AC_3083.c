#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 42
#define QUEUE_LEN 1600
#define is_valid(x, y) (x>=0 && x<row && y>=0 && y<col)
char maze[MAX_LEN][MAX_LEN];
int visited[MAX_LEN][MAX_LEN];
int row, col;
int start_x, start_y;
/* left, up, right, down */
const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};
/* right, up, left, down */
const int dx_right[] = {0, -1, 0, 1};
const int dy_right[] = {1, 0, -1, 0};
int lcount, rcount;
int head, tail;
struct EACH {
	int x, y;
	int mv;
} queue[QUEUE_LEN];


void
init()
{
	int i;
	char *p;
	memset(visited, 0, sizeof(visited));
	head = -1;
	tail = 0;
	lcount = rcount = 0;
	scanf("%d %d", &col, &row);
	for(i=0; i<row; i++) {
		scanf("%s", maze[i]);
		if((p=strchr(maze[i], 'S')) != NULL) {
			start_x = i;
			start_y = p-maze[i];
		}
	}
}

/*
 * dir: previous direction
 * switch(dir):
 *     case(right): up right down left (order)
 *     case(up):    left up right down
 *     case(left):  down left up right
 *     case(down):  right down left up
 */
void
dfs_left(int x, int y, int dir)
{
	int i, tx, ty;
	++lcount;
	if(maze[x][y] == 'E') {
		return;
	}
	dir = (dir+3)%4;
	for(i=0; i<4; i++) {
		tx = x + dx[(dir+i)%4];
		ty = y + dy[(dir+i)%4];
		if(is_valid(tx, ty) && maze[tx][ty]!='#') {
			dfs_left(tx, ty, (dir+i)%4);
			break;
		}
	}
}

void
dfs_right(int x, int y, int dir)
{
	int i, tx, ty;
	++rcount;
	if(maze[x][y] == 'E') 
		return;
	dir = (dir+3)%4;
	for(i=0; i<4; i++) {
		tx = x + dx_right[(dir+i)%4];
		ty = y + dy_right[(dir+i)%4];
		if(is_valid(tx, ty) && maze[tx][ty]!='#') {
			dfs_right(tx, ty, (dir+i)%4);
			break;
		}
	}
}

/*
 * from Internet: excellent code
int ok(int a,int b)
{
    if (a<0 || b<0 || a>=row || b>=col) return 0;
    if (maze[a][b]=='#') return 0;
    return 1;
}

void left(int j,int k)
{
    int dir,count=1;
    int a,b,bf=1;
    while (maze[j][k]!='E')
    {
          dir=(bf+3)%4;
          do{ 
                a=j+dx[dir];
                b=k+dy[dir];
                dir=(dir+1)%4;
          }while (!ok(a,b));
          j=a;
          k=b;
          bf=(dir+3)%4;
          count++;
    }
    printf("%d ",count);
}

void right(int j,int k)
{
    int dir,count=1;
    int a,b,bf=1;
    while (maze[j][k]!='E')
    {
          dir=(bf+1)%4;
          do{
                a=j+dx[dir];
                b=k+dy[dir];
                dir=(dir+3)%4;
          }while (!ok(a,b));
          j=a;
          k=b;
          bf=(dir+1)%4;
          count++;
    }
    printf("%d ",count);
}
*/

int 
bfs()
{
	int i, cx, cy, tx, ty, cmv;
	memset(visited, 0, sizeof(visited));
	queue[tail].x = start_x;
	queue[tail].y = start_y;
	queue[tail].mv = 1;
	visited[start_x][start_y] = 1;
	while(head < tail) {
		++head;
		cx = queue[head].x;
		cy = queue[head].y;
		cmv = queue[head].mv;
		if(maze[cx][cy] == 'E')
			return cmv;
		for(i=0; i<4; i++) {
			tx = cx + dx[i];
			ty = cy + dy[i];
			if(is_valid(tx, ty) && !visited[tx][ty] && maze[tx][ty]!='#') {
				++tail;
				queue[tail].x = tx;
				queue[tail].y = ty;
				queue[tail].mv = cmv+1;
				visited[tx][ty] = 1;
			}
		}
	}
}

int
main(int argc, char **argv)
{
	int tests;
	scanf("%d", &tests);
	while(tests--) {
		init();
		dfs_left(start_x, start_y, 1);
		dfs_right(start_x, start_y, 1);
		printf("%d %d %d\n", lcount, rcount, bfs());
	}
}

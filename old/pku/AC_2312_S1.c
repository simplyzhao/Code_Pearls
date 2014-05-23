/* 32MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 301
#define QUEUE_SIZE 90001
#define INF 0x7FFFFFFF
#define is_valid(x, y) ((x)>=0 && (x)<M && (y)>=0 && (y)<N)
char map[MAX_LEN][MAX_LEN];
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
int M, N;
int you_x, you_y, target_x, target_y;
int best[MAX_LEN][MAX_LEN]; /* important, best[i][j] stores the current 'best solution' at map[i][j] */
struct Node {
	int x, y;
} queue[QUEUE_SIZE];

int
bfs()
{
	int i, next_x, next_y, cur, head, tail;
	struct Node node;
	head = -1;
	tail = 0;
	queue[tail].x = you_x;
	queue[tail].y = you_y;
	best[you_x][you_y] = 0;
	while(head < tail) {
		++head;
		cur = best[queue[head].x][queue[head].y];
		for(i=0; i<4; i++) {
			node.x = queue[head].x + dx[i];
			node.y = queue[head].y + dy[i];
			if(is_valid(node.x, node.y)) {
				/* excellent, only push node which can be updated in 'best' into the queue */
				if(map[node.x][node.y] == 'E' || map[node.x][node.y] == 'T') {
					if(best[node.x][node.y] > cur+1) {
						best[node.x][node.y] = cur+1;
						++tail;
						queue[tail] = node;
					}
				} else if(map[node.x][node.y] == 'B') {
					if(best[node.x][node.y] > cur+2) {
						best[node.x][node.y] = cur+2;
						++tail;
						queue[tail] = node;
					}
				}
			}
		}
	}
}

int
main(int argc, char **argv)
{
	int i, j;
	while(scanf("%d %d", &M, &N)!=EOF && M && N) {
		for(i=0; i<M; i++) {
			scanf("%s", map[i]);
			for(j=0; j<N; j++) {
				if(map[i][j] == 'Y') {
					you_x = i;
					you_y = j;
				} else if(map[i][j] == 'T') {
					target_x = i; 
					target_y = j;
				}
				best[i][j] = INF;
			}
		}
		bfs();
		printf("%d\n", best[target_x][target_y]==INF ? -1 : best[target_x][target_y]);
	}
}

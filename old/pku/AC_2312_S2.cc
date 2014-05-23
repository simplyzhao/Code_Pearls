/* 0MS */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue> /* priority queue */
using namespace std;

#define MAX_LEN 301
#define is_valid(x, y) ((x)>=0 && (x)<M && (y)>=0 && (y)<N)
char map[MAX_LEN][MAX_LEN];
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
int M, N;
int you_x, you_y, target_x, target_y;
int visited[MAX_LEN][MAX_LEN];
struct Node {
	int x, y;
	int steps;
	bool operator<(const Node &item) const {
		return steps > item.steps;
	}
}cur, next;
priority_queue<Node> states;

int
bfs()
{
	int i;
	memset(visited, 0, sizeof(visited));
	while(!states.empty()) /* empty the queue */
		states.pop();
	next.x = you_x;
	next.y = you_y;
	next.steps = 0;
	visited[you_x][you_y] = 1;
	states.push(next);
	while(!states.empty()) {
		cur = states.top();
		states.pop();
		if(cur.x==target_x && cur.y==target_y)
			return cur.steps;
		for(i=0; i<4; i++) {
			next.x = cur.x + dx[i];
			next.y = cur.y + dy[i];
			if(!visited[next.x][next.y]) {
				visited[next.x][next.y] = 1;
				if(map[next.x][next.y]=='E' || map[next.x][next.y]=='T') {
					next.steps = cur.steps+1;
					states.push(next);
				} else if(map[next.x][next.y]=='B') {
					next.steps = cur.steps+2;
					states.push(next);
				}
			}
		}
	}
	return -1;
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
			}
		}
		printf("%d\n", bfs());
	}
}

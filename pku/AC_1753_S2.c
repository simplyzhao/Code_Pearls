/* 
 * BFS:
 * Memory: 648K Time: 16MS 
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 4
#define BIT_MAX 16
const int END_BLACK = 0;
const int END_WHITE = (1<<(BIT_MAX))-1;
/* up, down, left, right */
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int idx_diff[] = {-SIZE, SIZE, -1, 1};
struct State {
	long state;
	int count; /* minimum number of rounds needed to reach 'state' */
};
struct State queue[1<<BIT_MAX];
int visited[1<<BIT_MAX];
int head, tail;
long state; /* the low 16 bits represents the current state */

int
is_valid(int x, int y)
{
	return (x>=0 && x<SIZE && y>=0 && y<SIZE);
}

/*
 * tricky of bit-operation
 * 1 ^ x = ~x
 * 0 ^ x = x
 */
long
flip(long state, int x, int y)
{
	int i, index = x*SIZE + y;
	state ^= (1<<index);
	for(i=0; i<4; i++) {
		if(is_valid(x+dx[i], y+dy[i]))
			state ^= (1<<(index+idx_diff[i]));
	}
	return state;
}

int
bfs()
{
	int i, j, cur_count; 
	long cur_state, nxt_state;
	queue[tail].state = state;
	queue[tail].count = 0;
	visited[queue[tail].state] = 1;
	while(head < tail) {
		++head;
		cur_count = queue[head].count;
		cur_state = queue[head].state;
		if(cur_state==END_BLACK || cur_state==END_WHITE)
			return cur_count;
		for(i=0; i<SIZE; i++) {
			for(j=0; j<SIZE; j++) {
				nxt_state = flip(cur_state, i, j);
				if(!visited[nxt_state]) {
					visited[nxt_state] = 1;
					++tail;
					queue[tail].state = nxt_state;
					queue[tail].count = cur_count+1;
				}
			}
		}
	}
	return -1;
}

int 
main(int argc, char **argv)
{
	int i, j, index;
	char str[SIZE+1];
	/* Remember to initialize 'state' to be zero */
	state = index = tail = 0;
	head = -1;
	memset(visited, 0, sizeof(visited));
	for(i=0; i<SIZE; i++) {
		scanf("%s", str);
		for(j=0; j<SIZE; j++) {
			if(str[j] == 'w') 
				state += (1<<index);
			++index;
		}
	} 
	int rt = bfs();
	if(rt == -1)
		printf("Impossible\n");
	else
		printf("%d\n", rt);
	return 0;
}

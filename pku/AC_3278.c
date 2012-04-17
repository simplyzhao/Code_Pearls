#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 100001
int visited[MAX_NUM];
int n, k;
int head, tail;
struct EACH {
	int num;
	int moves;
} queue[MAX_NUM];

#define ADD(temp, cur) ++tail; \
			queue[tail].num = temp; \
			queue[tail].moves = cur+1; \
			visited[temp] = 1;

int
bfs()
{
	int cur_num, cur_moves, temp;
	queue[tail].num = n;
	queue[tail].moves = 0;
	visited[queue[tail].num] = 1;
	while(head <= tail) {
		++head;
		cur_num = queue[head].num;
		cur_moves = queue[head].moves;
		if(cur_num == k)
			return cur_moves;
		temp = cur_num - 1;
		if(temp>=0 && temp<MAX_NUM && !visited[temp]) {
			ADD(temp, cur_moves);
		}
		temp = cur_num + 1;
		if(temp>=0 && temp<MAX_NUM && !visited[temp]) {
			ADD(temp, cur_moves);
		}
		temp = cur_num<<1;
		if(temp>=0 && temp<MAX_NUM && !visited[temp]) {
			ADD(temp, cur_moves);
		}
	}
}

int
main(int argc, char **argv)
{
	while(scanf("%d %d", &n, &k)!=EOF) {
		memset(visited, 0, sizeof(visited));
		memset(queue, 0, sizeof(queue));
		head = -1;
		tail = 0;
		printf("%d\n", bfs());
	}
	return 0;
}

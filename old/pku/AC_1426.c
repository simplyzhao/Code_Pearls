#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define REMAINDER_MAX 201
#define QUEUE_MAX 100000

struct EACH {
	int remainder;
	int digit;
	struct EACH *pre;
}queue[QUEUE_MAX];
int hash[REMAINDER_MAX];
int head, tail;
int num;

void
output(struct EACH *end)
{
	if(end==NULL)
		return;
	output(end->pre);
	printf("%d", end->digit);
}

void
bfs()
{
	int cur_rem, next_rem;
	queue[tail].remainder = 1%num;
	queue[tail].digit = 1;
	queue[tail].pre = NULL;
	hash[queue[tail].remainder] = 1;
	while(head <= tail) {
		++head;
		cur_rem = queue[head].remainder;
		if(cur_rem == 0) {
			output(queue+head);
			printf("\n");
			return;
		}
		next_rem = (cur_rem*10+0)%num;
		if(!hash[next_rem]) {
			++tail;
			queue[tail].remainder = next_rem;
			queue[tail].digit = 0;
			queue[tail].pre = queue+head;
			hash[next_rem] = 1;
		}
		next_rem = (cur_rem*10+1)%num;
		if(!hash[next_rem]) {
			++tail;
			queue[tail].remainder = next_rem;
			queue[tail].digit = 1;
			queue[tail].pre = queue+head;
			hash[next_rem] = 1;
		}
	}
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &num)!=EOF && num!=0) {
		memset(hash, 0, sizeof(hash));
		memset(queue, 0, sizeof(queue));
		head = -1;
		tail = 0;
		bfs();
	}
}

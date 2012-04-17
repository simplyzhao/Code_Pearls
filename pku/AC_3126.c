#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define QUEUE_LEN 10000
int from, to;
int head, tail;
struct EACH {
	int plen;
	int num;
} queue[QUEUE_LEN];
int hash[QUEUE_LEN];

int
is_prime(int num)
{
	int i, up = (int)sqrt(num*1.0);
	for(i=2; i<=up; i++)
		if(num%i == 0)
			return 0;
	return 1;
}

int
bfs()
{
	int cur_plen, cur_num, next_num;
	int i, j, k, t, div;
	queue[tail].plen = 0;
	queue[tail].num = from;
	hash[queue[tail].num] = 1;
	while(head < tail) {
		++head;
		cur_plen = queue[head].plen;
		cur_num = queue[head].num;
		if(cur_num == to)
			return cur_plen;
		div = 1000;
		t = cur_num;
		for(i=3; i>=0; i--) {
			k = t/div;
			for(j=0; j<=9; j++) {
				if(i==3 && j==0)
					continue;
				next_num = cur_num;
				next_num -= k*div;
				next_num += j*div;
				if(!hash[next_num] && is_prime(next_num)) {
					++tail;
					queue[tail].plen = cur_plen + 1;
					queue[tail].num = next_num;
					hash[queue[tail].num] = 1;
				}
			}
			t = t%div;
			div /= 10;
		}
	}
	return -1;
}

int
main(int argc, char **argv)
{
	int i, tests, rt;
	scanf("%d", &tests);
	for(i=0; i<tests; i++) {
		scanf("%d %d", &from, &to);
		memset(queue, 0, sizeof(queue));
		memset(hash, 0, sizeof(hash));
		head = -1;
		tail = 0;
		rt = bfs();
		if(rt >= 0)
			printf("%d\n", rt);
		else
			printf("Impossible\n");
	}
	return 0;
}

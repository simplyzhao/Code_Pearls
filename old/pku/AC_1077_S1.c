/*
 * BFS
 * Memory: 6052K Time: 110MS
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define RC 3
#define STR_LEN 9
#define HASH_LEN 362880 /* 9! */
const int facs[] = {1, 2, 6, 24, 120, 720, 5040, 40320};
const char letters[] = "udlr";
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
char success[] = "123456780";
char begin[STR_LEN+1];
int success_hash, begin_position;
int hash[HASH_LEN];
struct EACH {
	char str[STR_LEN+1];
	int position;
	int pre;
	int dir;
} queue[HASH_LEN];

/* permutation -> number */
int 
hash_func(char *str)
{
	int i, j, cnt, result = 0;
	for(i=1; i<STR_LEN; i++) {
		cnt = 0;
		for(j=0; j<i; j++)
			if(str[j] > str[i])
				++cnt;
		result += (cnt*facs[i-1]);
	}
	return result;
}

void
init()
{
	int i;
	char input[2];
	memset(hash, 0, sizeof(hash));
	for(i=0; i<STR_LEN; i++) {
		scanf("%s", input);
		begin[i] = input[0];
		if(begin[i] == 'x') {
			begin[i] = '0';
			begin_position = i;
		}
	}
	begin[STR_LEN] = '\0';
	success_hash = hash_func(success);
}

void
output(int index)
{
	if(queue[index].pre == -1)
		return;
	output(queue[index].pre);
	printf("%c", letters[queue[index].dir]);
}

#define ADD(tail, s, pos, p, d) strcpy(queue[tail].str, s); \
	queue[tail].position = pos; \
	queue[tail].pre = p; \
	queue[tail].dir = d;

#define CHECK(h) if(h == success_hash) { \
	output(tail); \
	printf("\n"); \
	return; \
}

void
bfs()
{
	int i, h, head, tail;
	char nxt[STR_LEN+1];
	int curx, cury, nxtx, nxty;
	head = -1;
	tail = 0;
	ADD(tail, begin, begin_position, -1, -1);
	h = hash_func(begin);
	hash[h] = 1;
	CHECK(h);
	while(head < tail) {
		++head;
		curx = queue[head].position/RC;
		cury = queue[head].position%RC;
		for(i=0; i<4; i++) {
			nxtx = curx + dx[i];
			nxty = cury + dy[i];
			if(nxtx>=0 && nxtx<RC && nxty>=0 && nxty<RC) {
				strcpy(nxt, queue[head].str);
				nxt[queue[head].position] = nxt[nxtx*RC+nxty];
				nxt[nxtx*RC+nxty] = '0';
				h = hash_func(nxt);
				if(!hash[h]) {
					++tail;
					ADD(tail, nxt, nxtx*RC+nxty, head, i);
					hash[h] = 1;
					CHECK(h);
				}
			}
		}
	}
	printf("unsolvable\n");
}

int
main(int argc, char **argv)
{
	init();
	bfs();
	return 0;
}

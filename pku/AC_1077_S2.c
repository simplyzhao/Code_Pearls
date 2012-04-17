/*
 * BBFS [Memory: 3564K Time: 16MS]
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define RC 3
#define STR_LEN 9
#define HASH_LEN 362880 /* 9! */
const int facs[] = {1, 2, 6, 24, 120, 720, 5040, 40320};
const char letters[] = "udlr";
const int pos[] = {-3, 3, -1, 1}; /* up, down, left, right */
const int movable[][4] = {0,1,0,1, 0,1,1,1, 0,1,1,0, 1,1,0,1, 1,1,1,1, 1,1,1,0, 1,0,0,1, 1,0,1,1, 1,0,1,0};
int hash[2][HASH_LEN];
struct EACH {
	char str[STR_LEN+1];
	int position, pre, dir, hval;
} queue[2][HASH_LEN];

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
output(int hash_value)
{
	int i, j;
	char tmp[250];
	for(i=0; i<HASH_LEN; i++)
		if(queue[0][i].hval == hash_value)
			break;
	j = 0;
	while(queue[0][i].pre != -1) {
		tmp[j++] = letters[queue[0][i].dir];
		i = queue[0][i].pre;
	}
	for(i=j-1; i>=0; i--)
		printf("%c", tmp[i]);

	for(i=0; i<HASH_LEN; i++)
		if(queue[1][i].hval == hash_value)
			break;
	while(queue[1][i].pre != -1) {
		printf("%c", queue[1][i].dir%2==0 ? letters[queue[1][i].dir+1] : letters[queue[1][i].dir-1]);
		i = queue[1][i].pre;
	}
}

#define ADD(index, tail, s, pos, p, d, h) strcpy(queue[index][tail].str, s); \
	queue[index][tail].position = pos; \
	queue[index][tail].pre = p; \
	queue[index][tail].dir = d; \
	queue[index][tail].hval = h;

int
bfs(char *start_str, int start_pos)
{
	int i, index, h, curp, nxtp, head[2], tail[2];
	char suc[] = "123456780";
	char nxt[STR_LEN+1];
	head[0] = head[1] = -1;
	tail[0] = tail[1] = 0;
	h = hash_func(start_str);
	hash[0][h] = 1;
	ADD(0, tail[0], start_str, start_pos, -1, -1, h);
	h = hash_func(suc);
	hash[1][h] = 1;
	ADD(1, tail[1], suc, 8, -1, -1, h);
	while(head[0]<tail[0] && head[1]<tail[1]) {
		for(index=0; index<2; index++) {
			++head[index];
			curp = queue[index][head[index]].position;
			for(i=0; i<4; i++) {
				if(movable[curp][i]) {
					nxtp = curp + pos[i];
					strcpy(nxt, queue[index][head[index]].str);
					nxt[curp] = nxt[nxtp];
					nxt[nxtp] = '0';
					h = hash_func(nxt);
					if(!hash[index][h]) {
						++tail[index];
						ADD(index, tail[index], nxt, nxtp, head[index], i, h);
						hash[index][h] = 1;
					}
					if(hash[1-index][h])
						return h;
				}
			}
		}
	}
	return -1;
}

int
main(int argc, char **argv)
{
	int i, sp, h;
	char input[2], num[STR_LEN+1];
	for(i=0; i<STR_LEN; i++) {
		scanf("%s", input);
		num[i] = input[0];
		if(num[i]=='x') {
			num[i] = '0';
			sp = i;
		}
	}
	num[STR_LEN] = '\0';
	h = bfs(num, sp);
	if(h==-1)
		printf("unsolvable\n");
	else {
		output(h);
		printf("\n");
	}
	return 0;
}

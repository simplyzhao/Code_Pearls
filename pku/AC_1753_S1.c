/*
 * DFS:
 * Memory: 356K Time: 16MS
 */ 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 4
#define BIT_MAX 16
const int END_BLACK = 0;
const int END_WHITE = (1<<(BIT_MAX))-1;
int min;

int
flip(int init_state, int bit_num)
{
	int x, y;
	x = bit_num / SIZE;
	y = bit_num % SIZE;
	init_state ^= (1<<bit_num);
	if(x == 0)
		init_state ^= (1<<(bit_num+SIZE));
	else if(x == 3)
		init_state ^= (1<<(bit_num-SIZE));
	else {
		init_state ^= (1<<(bit_num+SIZE));
		init_state ^= (1<<(bit_num-SIZE));
	}
	if(y==0)
		init_state ^= (1<<(bit_num+1));
	else if(y==3)
		init_state ^= (1<<(bit_num-1));
	else {
		init_state ^= (1<<(bit_num+1));
		init_state ^= (1<<(bit_num-1));
	}
	return init_state;
}

void 
dfs(long state, int depth, int count)
{
	if(state==END_BLACK || state==END_WHITE) {
		min = count < min ? count : min;
		return;
	}
	if(depth >= BIT_MAX || count >= min)
		return;
	dfs(state, depth+1, count);
	dfs(flip(state, depth), depth+1, count+1);
}

int 
main(int argc, char **argv)
{
	int i, j, index;
	/* Attention: long should be used, int caused error */
    long state; /* the low 16 bits represents the current state */
	char str[SIZE+1];
	min = 32767;
	/* Remember to initialize 'state' to be zero */
	state = index = 0;
	for(i=0; i<SIZE; i++) {
		scanf("%s", str);
		for(j=0; j<SIZE; j++) {
			if(str[j] == 'w') 
				state += (1<<index);
			++index;
		}
	} 
	dfs(state, 0, 0);
	if(min == 32767)
		printf("Impossible\n");
	else
		printf("%d\n", min);
	return 0;
}

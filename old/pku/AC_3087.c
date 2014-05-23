#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STACK_LEN 101
#define MAX_LEN STACK_LEN*2
#define PRIME 100003
#define QUEEN_LEN 10000
char tmp1[STACK_LEN], tmp2[STACK_LEN];
char desire[MAX_LEN];
char queue[QUEEN_LEN][MAX_LEN];
int len;

struct Node {
	int index;
	struct Node *next; /* collision: chaining */
} *hash[PRIME];

int ELFHash(char *str)
{
	unsigned long t, hash = 0;
	while(*str) {
		hash = (hash<<4) + (*str++);
		if((t = hash&0xF0000000L))
			hash ^= t>>24;
		hash &= ~t;
	}
	return (hash & 0x7FFFFFFF)%PRIME;
}

void
insert(int hash_val, int index)
{
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	node->index = index;
	node->next = hash[hash_val];
	hash[hash_val] = node;
}

int
search(char *f_word)
{
	int hash_val = ELFHash(f_word);
	struct Node *node = hash[hash_val];
	while(node != NULL) {
		if(strcmp(f_word, queue[node->index]) == 0)
			return node->index;
		node = node->next;
	}
	return -1;
}

int
shuffle()
{
	int i, count = 0;
	int hash_val;
	memset(hash, 0, sizeof(hash));
	while(1) {
		for(i=0; i<2*len; i++) {
			if(i%2==0)
				queue[count][i] = tmp2[i/2];
			else
				queue[count][i] = tmp1[i/2];
		}
		queue[count][i] = '\0';
		strncpy(tmp1, queue[count], len);
		strncpy(tmp2, queue[count]+len, len);
		if(strcmp(queue[count], desire) == 0)
			return count+1;
		if(search(queue[count]) != -1)
			return -1;
		hash_val = ELFHash(queue[count]);
		insert(hash_val, count);
		++count;
	}
}

int
main(int argc, char **argv)
{
	int i, tests;
	scanf("%d", &tests);
	for(i=1; i<=tests; i++) {
		scanf("%d", &len);
		scanf("%s", tmp1);
		scanf("%s", tmp2);
		scanf("%s", desire);
		printf("%d %d\n", i, shuffle());
	}
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 100001
#define MAX_LEN 12
#define PRIME 100003
struct Node {
	int index;
	struct Node *next; /* collision: chaining */
} *hash[PRIME] = {NULL};
char eng[MAX_NUM][MAX_LEN];
char flg[MAX_NUM][MAX_LEN];

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
	if(node == NULL) {
		fprintf(stderr, "malloc error in: insert\n");
		exit(1);
	}
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
		if(strcmp(f_word, flg[node->index]) == 0)
			return node->index;
		node = node->next;
	}
	return -1;
}

void
input_hash()
{
	int hash_val, index = 0;
	char tmp[MAX_LEN*2+1];
	memset(hash, 0, sizeof(hash));
	while(gets(tmp) && tmp[0]) {
		sscanf(tmp, "%s %s", eng[index], flg[index]);
		hash_val = ELFHash(flg[index]);
		insert(hash_val, index);
		++index;
	}
}

int
main(int argc, char **argv)
{
	int rt;
	char f_word[MAX_LEN];
	input_hash();
	while(scanf("%s", f_word) != EOF) {
		rt = search(f_word);
		printf("%s\n", rt==-1 ? "eh" : eng[rt]);
	}
}

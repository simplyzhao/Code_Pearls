/* word frequency statistics, using Hash-Table, from Programming Pearl */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define WORD_BUF 128
#define NHASH 29989 /* prime number just bigger than needed */
#define MULT 31

struct HNode {
	char *word;
	int count;
	struct HNode *next;
};
struct HNode *Hash[NHASH] = {NULL}; 

#define NODEGROUP 1000
struct HNode *nodebuf;
int nodeleft = 0;

struct HNode *
node_alloc()
{
	if(nodeleft == 0) {
		nodebuf = (struct HNode *)malloc(NODEGROUP * sizeof(struct HNode));
		nodeleft = NODEGROUP;
	}
	--nodeleft;
	return (nodebuf++);
}

unsigned int
hash(char *str) /* a simple implementation of string-hash, others like ELFHash... */
{
	unsigned int ret = 0;
	char *ptr;
	for(ptr=str; *ptr; ++ptr)
		ret = ret * MULT + (*ptr);
	return (ret % NHASH);
}

void
insert_hash(char *word)
{
	struct HNode *node;
	unsigned int h = hash(word);
	for(node=Hash[h]; node!=NULL; node=node->next)
		if(strcmp(node->word, word) == 0) {
			++(node->count);
			return;
		}
	struct HNode *pend = node_alloc();
	pend->word = strdup(word);
	pend->count = 1;
	pend->next = Hash[h];
	Hash[h] = pend;
}

int
main(int argc, char **argv)
{
	char buf[WORD_BUF];
	while(scanf("%s", buf) != EOF) {
		insert_hash(buf);
	}

	int i;
	struct HNode *node;
	for(i=0; i<NHASH; ++i) 
		for(node=Hash[i]; node!=NULL; node=node->next) 
			printf("%s\t%d\n", node->word, node->count);

	return 0;
}

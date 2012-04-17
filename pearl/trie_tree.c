/* implementation of Trie-Tree/Dictionary-Tree */
/* used to calculate word frequency */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define WIDTH 26
#define MAX_WORD_LEN 101

struct Trie_Node {
	int count;
	struct Trie_Node *next[WIDTH];
};
static struct Trie_Node root = {0, {NULL}}; /* root of trie-tree, has no character associated */

void 
trie_tree_insert(const char *word)
{
	const char *ptr = word;
	struct Trie_Node *tmp, *cur = &root;
	while(*ptr) {
		if(cur->next[(*ptr)-'a'] == NULL) {
			tmp = (struct Trie_Node *)malloc(sizeof(struct Trie_Node));
			memset(tmp, 0, sizeof(struct Trie_Node));
			cur->next[(*ptr)-'a'] = tmp;
		}
		cur = cur->next[(*ptr)-'a'];
		++ptr;
	}
	++(cur->count);
}

void
trie_tree_travel(struct Trie_Node *node, int pos)
{
	int i;
	static char buf[MAX_WORD_LEN];
	if(node == NULL)
		return;
	if(node->count) {
		buf[pos] = '\0';
		printf("%s : %d\n", buf, node->count);
	}
	for(i=0; i<WIDTH; i++) {
		if(node->next[i]) {
			buf[pos] = 'a'+i;
			trie_tree_travel(node->next[i], pos+1);
		}
	}
}

int
main(int argc, char **argv)
{
	char buf[MAX_WORD_LEN];
	while(scanf("%s", buf) != EOF)
		trie_tree_insert(buf);

	trie_tree_travel(&root, 0);
}

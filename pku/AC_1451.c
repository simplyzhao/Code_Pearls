#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define WIDTH 26 /* lowercase letters */
#define MAX_LEN 101
const char *keys[] = {
	"",
	"",
	"abc", 
	"def",
	"ghi",
	"jkl",
	"mno",
	"pqrs",
	"tuv",
	"wxyz" };
const int keys_len[] = {0, 0, 3, 3, 3, 3, 3, 4, 3, 4};

struct Trie_Node {
	int freq;
	struct Trie_Node *next[WIDTH];
};
struct Trie_Node root = {0, {NULL}};
char buf[MAX_LEN], ret[MAX_LEN];
int max_freq;

void
trie_tree_insert(const char *word, int count)
{
	struct Trie_Node *tmp, *cur = &root;
	const char *ptr = word;
	while(*ptr) {
		if(cur->next[(*ptr)-'a'] == NULL) {
			tmp = (struct Trie_Node *)malloc(sizeof(struct Trie_Node));
			memset(tmp, 0, sizeof(struct Trie_Node));
			cur->next[(*ptr)-'a'] = tmp;
		}
		cur = cur->next[(*ptr)-'a'];
		cur->freq += count;
		++ptr;
	}
}

void
init()
{
	char word[MAX_LEN];
	int num, count;
	scanf("%d", &num);
	while(num--) {
		scanf("%s %d", word, &count);
		trie_tree_insert(word, count);
	}
}

void
trie_tree_search(struct Trie_Node *node, char *digits, int depth, int len)
{
	if(depth == len) {
		if(node->freq > max_freq) {
			max_freq = node->freq;
			memcpy(ret, buf, len);
		}
		return;
	}
	int i, index = digits[depth] - '0';
	for(i=0; i<keys_len[index]; i++) {
		if(node->next[keys[index][i]-'a']) {
			buf[depth] = keys[index][i];
			trie_tree_search(node->next[keys[index][i]-'a'], digits, depth+1, len);
		}
	}
}

void
do_job()
{
	int i, len, nm;
	char digits[MAX_LEN+1];
	scanf("%d", &nm);
	while(nm--) {
		scanf("%s", digits);
		len = strlen(digits);
		for(i=1; i<len; i++) {
			max_freq = -1;
			trie_tree_search(&root, digits, 0, i);
			if(max_freq == -1)
				printf("MANUALLY\n");
			else {
				ret[i] = '\0';
				printf("%s\n", ret);
			}
		}
		printf("\n");
	}
}

void
trie_tree_free(struct Trie_Node *node)
{
	int i;
	for(i=0; i<WIDTH; i++) {
		if(node->next[i])
			trie_tree_free(node->next[i]);
		node->next[i] = NULL;
	}
	if(node != &root)
		free(node);
}

int
main(int argc, char **argv)
{
	int i, tests;
	scanf("%d", &tests);
	for(i=1; i<=tests; i++) {
		printf("Scenario #%d:\n", i);
		init();
		do_job();
		trie_tree_free(&root);
		printf("\n");
	}
}

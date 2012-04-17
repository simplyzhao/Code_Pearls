/*
 * BOP 3.2
 * telephone number  <---->  word
 *
 * Solution: Trie Tree (Dictionary Tree)
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int bool;
#define CHARACTER_SET 26
#define LEN_MAX 16
const char *keyboard[] = {
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
const int keyboard_len[] = {0, 0, 3, 3, 3, 3, 3, 4, 3, 4};

struct Node {
	bool end;
	struct Node *links[CHARACTER_SET];
};
static struct Node root = {0, {NULL}};

void
trie_tree_insert(const char *word)
{
	struct Node *ptr = &root;
	while(word && *word) {
		if(ptr->links[*word-'a'] == NULL) {
			ptr->links[*word-'a'] = (struct Node *)malloc(sizeof(struct Node));
			memset(ptr->links[*word-'a'], 0, sizeof(struct Node));
		}
		ptr = ptr->links[*word-'a'];
		++word;
	}
	ptr->end = 1;
}

void
trie_tree_find(const char *phone, char *ret, struct Node *node, int depth)
{
	if(*phone == '\0') {
		if(node->end) {
			ret[depth] = '\0';
			fprintf(stdout, "%s\n", ret);
		}
		return;
	}
	char ch;
	int i;
	for(i=0; i<keyboard_len[*phone-'0']; ++i) {
		ch = keyboard[*phone-'0'][i];
		if(node->links[ch-'a'] != NULL) {
			ret[depth] = ch;
			trie_tree_find(phone+1, ret, node->links[ch-'a'], depth+1);
		}
	}
}

int
main(int argc, char **argv)
{
	char word[LEN_MAX+1], phone[LEN_MAX+1];
	while(scanf("%s", word) != EOF) {
		trie_tree_insert(word);
		printf("TRIE INSERT: %s\n", word);
	}

	fprintf(stdout, "\nPhone2Word Match\n");

	while(scanf("%s", phone) != EOF)
		trie_tree_find(phone, word, &root, 0);

	return 0;
}

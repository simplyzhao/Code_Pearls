/* binary search tree(dynamic allocation) */
/* 544K 1188MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define MAX_LEN 36
struct Node {
	char spec[MAX_LEN];
	int count;
	struct Node *left, *right;
};
int total;

struct Node *
create_node(char *str)
{	
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	assert(node != NULL);
	strcpy(node->spec, str);
	node->left = node->right = NULL;
	node->count = 1;
	return node;
}

void
insert(struct Node **root, char *str)
{
	int ret;
	struct Node *node;
	if(*root==NULL) {
		*root = create_node(str);
		return;
	}
	ret = strcmp((*root)->spec, str);
	if(ret == 0)
		++((*root)->count);
	else if(ret < 0)
		insert(&((*root)->right), str);
	else
		insert(&((*root)->left), str);
}

void
inorder(struct Node *root)
{
	if(root == NULL)
		return;
	inorder(root->left);
	printf("%s %.4f\n", root->spec, (root->count)*100.0/total);
	inorder(root->right);
}

void
destroy(struct Node **root)
{
}

int
main(int argc, char **argv)
{
	char str[MAX_LEN];
	struct Node *bst = NULL;
	total = 0;
	while(gets(str) != NULL) {
		++total;
		insert(&bst, str);
	}
	inorder(bst);
}

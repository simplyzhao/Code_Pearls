#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * BoP 3.9
 * given the preorder and inorder, rebuild the tree
 */
struct Node {
	struct Node *left;
	struct Node *right;
	char value;
};

void
rebuild(char *preOrder, char *inOrder, int LEN, struct Node **root)
{
	if(LEN == 0) {
		*root = NULL;
		return;
	}

	*root = (struct Node *)malloc(sizeof(struct Node));
	(*root)->value = preOrder[0];

	int i;
	for(i=0; i<LEN; i++)
		if(inOrder[i] == preOrder[0])
			break;
	rebuild(preOrder+1, inOrder, i, &((*root)->left));
	rebuild(preOrder+i+1, inOrder+i+1, LEN-i-1, &((*root)->right));
}

/* FOR TEST ONLY */
void
preorder(struct Node *root)
{
	if(root == NULL)
		return;
	printf("%c\t", root->value);
	preorder(root->left);
	preorder(root->right);
}

void
inorder(struct Node *root)
{
	if(root == NULL)
		return;
	inorder(root->left);
	printf("%c\t", root->value);
	inorder(root->right);
}

int
main(int argc, char **argv)
{
	char pre[] = "abdcef";
	char in[] = "dbaecf";
	struct Node *root;

	rebuild(pre, in, 6, &root);

	preorder(root);
	printf("\n");
	inorder(root);
	printf("\n");

	return 0;
}

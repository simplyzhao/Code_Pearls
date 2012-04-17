#include "bstree.h"

int
compare(const void *arg1, const void *arg2)
{
	return strcmp((char *)arg1, (char *)arg2);
}

void
print(const void *arg)
{
	printf("%s\n", (char *)arg);
}

int
main(int argc, char **argv)
{
	struct BSTree *bst = create_bstree(compare, NULL);

	bstree_insert(bst, "Beautiful");
	bstree_insert(bst, "Unlikely");
	bstree_insert(bst, "Check");
	bstree_insert(bst, "Desktop");
	bstree_insert(bst, "Machine");
	bstree_insert(bst, "Applet");

	printf("-------------InOrder-------------\n");
	bstree_inorder_walk(bst, print);
	printf("-------------PreOrder-------------\n");
	bstree_preorder_walk(bst, print);
	printf("-------------PostOrder-------------\n");
	bstree_postorder_walk(bst, print);

	printf("-----------------Statistics------------------\n");
	printf("Count: %d\n", bstree_count(bst));
	printf("Height: %d\n", bstree_height(bst));
	printf("Minimum: %s\n", (char *)(bstree_minimum(bst)->val));
	printf("Maximum: %s\n", (char *)(bstree_maximum(bst)->val));

	struct TNode *t = bstree_find(bst, "Beautiful");
	bstree_remove_node(bst, t, TRUE);

	bstree_remove(bst, "Unlikely", TRUE);
	
	printf("-------------InOrder-------------\n");
	bstree_inorder_walk(bst, print);
	printf("-------------PreOrder-------------\n");
	bstree_preorder_walk(bst, print);
	printf("-------------PostOrder-------------\n");
	bstree_postorder_walk(bst, print);

	printf("-----------------Statistics------------------\n");
	printf("Count: %d\n", bstree_count(bst));
	printf("Height: %d\n", bstree_height(bst));
	printf("Minimum: %s\n", (char *)(bstree_minimum(bst)->val));
	printf("Maximum: %s\n", (char *)(bstree_maximum(bst)->val));

	destroy_bstree(bst, TRUE);
}

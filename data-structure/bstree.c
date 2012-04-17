#include "bstree.h"

struct BSTree {
	struct TNode *root;
	int count;
	compare_func compare;
	release_func release;
};

struct BSTree *
create_bstree(compare_func comp, release_func rel)
{
	struct BSTree *bstree = (struct BSTree *)malloc(sizeof(struct BSTree));
	if(bstree) {
		if(comp == NULL) {
			free(bstree);
			bstree = NULL;
		} else {
			bstree->root = NULL;
			bstree->count = 0;
			bstree->compare = comp;
			bstree->release = rel;
		}
	}
	return bstree;
}

static void
destroy_bstree_node(struct TNode *root, release_func release, BOOL mem_release)
{
	if(root == NULL)
		return;
	destroy_bstree_node(root->left, release, mem_release);
	destroy_bstree_node(root->right, release, mem_release);
	if(release && mem_release)
		release(root->val);
	free(root);
}

void
destroy_bstree(struct BSTree *bstree, BOOL mem_release)
{
	if(bstree) {
		destroy_bstree_node(bstree->root, bstree->release, mem_release);

		free(bstree);
	}
}

BOOL
bstree_insert(struct BSTree *bstree, void *data)
{
	assert(bstree != NULL);

	if(data == NULL)
		return FALSE;
	struct TNode *new_node = (struct TNode *)malloc(sizeof(struct TNode));
	if(new_node == NULL)
		return FALSE;
	new_node->val = data;
	new_node->left = new_node->right = new_node->parent = NULL;

	struct TNode *ptr, *node = bstree->root;
	ptr = NULL;
	while(node != NULL) {
		ptr = node;
		if(bstree->compare(node->val, data) >= 0)
			node = node->left;
		else
			node = node->right;
	}
	new_node->parent = ptr;
	if(ptr == NULL)
		bstree->root = new_node;
	else {
		if(bstree->compare(ptr->val, data) >= 0)
			ptr->left = new_node;
		else
			ptr->right = new_node;
	}
	++(bstree->count);
	return TRUE;
}

BOOL
bstree_remove(struct BSTree *bstree, void *data, BOOL mem_release)
{
	struct TNode *target = bstree_find(bstree, data);
	bstree_remove_node(bstree, target, mem_release);
}

BOOL 
bstree_remove_node(struct BSTree *bstree, struct TNode *target, BOOL mem_release)
{
	assert(bstree != NULL);

	if(target == NULL)
		return FALSE;

	struct TNode *ptr, *node;
	if(target->left==NULL || target->right==NULL)
		node = target;
	else
		node = bstree_successor(bstree, target);

	if(node->left != NULL)
		ptr = node->left;
	else
		ptr = node->right;
	if(ptr != NULL) 
		ptr->parent = node->parent;
	if(node->parent == NULL)
		bstree->root = ptr;
	else {
		if(node == node->parent->left)
			node->parent->left = ptr;
		else
			node->parent->right = ptr;
	}

	if(target != node) { /* copy satellite data */
		void *tmp = target->val;
		target->val = node->val;
		node->val = tmp;
	}

	if(bstree->release && mem_release)
		bstree->release(node->val);
	free(node);

	--(bstree->count);
	return TRUE;
}

struct TNode *
bstree_find(struct BSTree *bstree, void *data)
{
	assert(bstree != NULL);

	if(data == NULL)
		return NULL;
	struct TNode *ptr = bstree->root;
	int ret;
	while(ptr != NULL) {
		ret = bstree->compare(ptr->val, data);
		if(ret == 0)
			return ptr;
		else if(ret >= 0)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	return NULL;
}

static struct TNode *
bstree_minimum_node(struct TNode *root)
{	
	struct TNode *ptr = root;
	while(ptr && ptr->left)
		ptr = ptr->left;
	return ptr;
}
struct TNode *
bstree_minimum(struct BSTree *bstree)
{
	assert(bstree != NULL);
	return bstree_minimum_node(bstree->root);
}

static struct TNode *
bstree_maximum_node(struct TNode *root)
{	
	struct TNode *ptr = root;
	while(ptr && ptr->right)
		ptr = ptr->right;
	return ptr;
}
struct TNode *
bstree_maximum(struct BSTree *bstree)
{
	assert(bstree != NULL);
	return bstree_maximum_node(bstree->root);
}

struct TNode *
bstree_successor(struct BSTree *bstree, struct TNode *target)
{
	assert(bstree!=NULL && target!=NULL);
	if(target->right != NULL) 
		return bstree_minimum_node(target->right);
	struct TNode *ptr, *node = target;
	ptr = node->parent;
	while(ptr != NULL) {
		if(ptr->left == node)
			break;
		node = ptr;
		ptr = node->parent;
	}
	return ptr;
}

struct TNode *
bstree_predecessor(struct BSTree *bstree, struct TNode *target)
{
	assert(bstree!=NULL && target!=NULL);
	if(target->left)
		return bstree_maximum_node(target->left);
	struct TNode *ptr, *node = target;
	ptr = node->parent;
	while(ptr != NULL) {
		if(ptr->right == node)
			break;
		node = ptr;
		ptr = node->parent;
	}
	return ptr;
}

static void
bstree_inorder_walk_node(struct TNode *root, foreach_func apply)
{
	if(root == NULL)
		return;
	bstree_inorder_walk_node(root->left, apply);
	apply(root->val);
	bstree_inorder_walk_node(root->right, apply);
}
void
bstree_inorder_walk(struct BSTree *bstree, foreach_func apply)
{
	assert(bstree != NULL);
	if(apply != NULL)
		return bstree_inorder_walk_node(bstree->root, apply);
}

static void
bstree_preorder_walk_node(struct TNode *root, foreach_func apply)
{	
	if(root == NULL)
		return;
	apply(root->val);
	bstree_preorder_walk_node(root->left, apply);
	bstree_preorder_walk_node(root->right, apply);
}
void
bstree_preorder_walk(struct BSTree *bstree, foreach_func apply)
{
	assert(bstree != NULL);
	if(apply)
		return bstree_preorder_walk_node(bstree->root, apply);
}

static void
bstree_postorder_walk_node(struct TNode *root, foreach_func apply)
{   
	if(root == NULL)
		return;
	bstree_postorder_walk_node(root->left, apply);
	bstree_postorder_walk_node(root->right, apply);
	apply(root->val);
}
void
bstree_postorder_walk(struct BSTree *bstree, foreach_func apply)
{
	assert(bstree != NULL);
	if(apply)
		return bstree_postorder_walk_node(bstree->root, apply);
}

int
bstree_count(struct BSTree *bstree)
{
	assert(bstree != NULL);
	return (bstree->count);
}

static int
bstree_height_node(struct TNode *root)
{
	if(root == NULL)
		return 0;
	int lh, rh, ret;
	lh = bstree_height_node(root->left);
	rh = bstree_height_node(root->right);
	ret = lh >= rh ? lh : rh;
	return (ret+1);
}
int
bstree_height(struct BSTree *bstree)
{
	assert(bstree != NULL);
	return bstree_height_node(bstree->root);
}

BOOL
bstree_is_empty(struct BSTree *bstree)
{
	assert(bstree != NULL);
	return ((bstree->count) == 0);
}

#ifndef __BSTREE_H
#define __BSTREE_H

/* 
 * implementation of binary search tree 
 * Note:
 * you have the capability to control whether or not to release the memory related
 * to the pointer when remove it from the tree 
 * if you wanna, provide a 'release_func', plus set 'mem_release' TRUE in
 * destroy and remove methods, otherwise, you just have to take care of the
 * memory yourself
 */
#include "basic.h"

struct TNode {
	void *val;
	struct TNode *left, *right;
	struct TNode *parent;
};

struct BSTree;

struct BSTree *create_bstree(compare_func, release_func);
void destroy_bstree(struct BSTree *, BOOL mem_release);

BOOL bstree_insert(struct BSTree *, void *);
BOOL bstree_remove(struct BSTree *, void *, BOOL mem_release);
BOOL bstree_remove_node(struct BSTree *, struct TNode *, BOOL mem_release);

struct TNode *bstree_find(struct BSTree *, void *);
struct TNode *bstree_minimum(struct BSTree *);
struct TNode *bstree_maximum(struct BSTree *);
struct TNode *bstree_successor(struct BSTree *, struct TNode *);
struct TNode *bstree_predecessor(struct BSTree *, struct TNode *);

void bstree_inorder_walk(struct BSTree *, foreach_func);
void bstree_preorder_walk(struct BSTree *, foreach_func);
void bstree_postorder_walk(struct BSTree *, foreach_func);

int bstree_count(struct BSTree *);
int bstree_height(struct BSTree *);
BOOL bstree_is_empty(struct BSTree *);

#endif

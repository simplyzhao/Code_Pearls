/*
 * Problem:
 *     given a binary tree as follows:
 *         struct TreeNode {
 *             struct TreeNode *left;
 *             struct TreeNode *right;
 *             struct TreeNode *next;
 *         }
 *     1. how to transversal and link each node level by level with 'next'?
 */
#include<stdio.h>
typedef int Element;
struct TreeNode {
	Element element;
	struct TreeNode *left;
	struct TreeNode *right;
	struct TreeNode *next;
};

struct TreeNode *
transversal_linklist(struct TreeNode *root)
{
	struct TreeNode *head, *cur, *tail;
	head = cur = tail = root;
	while(cur != NULL) {
		if(cur->left != NULL) {
			tail->next = cur->left;
			tail = tail->next;
		}
		if(cur->right != NULL) {
			tail->next = cur->right;
			tail = tail->next;
		}
		cur = cur->next;
	}
	return head;
}

/* ---------------------test----------------------- */
int
main(int argc, char **argv)
{
	struct TreeNode a, b, c, d, e, f;
	a.left = &b;
	a.right = &c;
	a.element = 1;
	a.next = NULL;

	b.left = NULL;
	b.right = &d;
	b.element = 2;
	b.next = NULL;

	c.left = &e;
	c.right = NULL;
	c.element = 3;
	c.next = NULL;

	d.left = &f;
	d.right = NULL;
	d.element = 4;
	d.next = NULL;

	e.left = NULL;
	e.right = NULL;
	e.element = 5;
	e.next = NULL;

	f.left = NULL;
	f.right = NULL;
	f.element = 6;
	f.next = NULL;

	struct TreeNode *r;
	r = transversal_linklist(&a);

	for( ; r!=NULL; r=r->next)
		printf("%d\t", r->element);
	printf("\n");
}

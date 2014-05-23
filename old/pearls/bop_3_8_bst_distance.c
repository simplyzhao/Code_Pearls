#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX(a, b) ((a)>=(b) ? (a) : (b))
struct Node {
	char value;
	struct Node *left, *right;
	int lmax, rmax;
};
int ret;

void
solve_max_distance(struct Node *root)
{
	if(root->left == NULL)
		root->lmax = 0;
	if(root->right == NULL)
		root->rmax = 0;

	if(root->left)
		solve_max_distance(root->left);
	if(root->right)
		solve_max_distance(root->right);

	if(root->left)
		root->lmax = MAX(root->left->lmax, root->left->rmax) + 1;
	if(root->right)
		root->rmax = MAX(root->right->lmax, root->right->rmax) + 1;

	ret = MAX(ret, root->lmax + root->rmax);
}

int
main(int argc, char **argv)
{
	ret = 0;
	struct Node a, b, c, d, e, f, g, h, i;
	i.value = 'i';
	i.left = i.right = NULL;
	h.value = 'h';
	h.left = h.right = NULL;
	g.value = 'g';
	g.right = &i;
	g.left = NULL;
	f.value = 'f';
	f.left = &h;
	f.right = NULL;
	e.value = 'e';
	e.left = e.right = NULL;
	d.value = 'd';
	d.left = &f;
	d.right = &g;
	c.value = 'c';
	c.left = c.right = NULL;
	b.value = 'b';
	b.left = &d;
	b.right = &e;
	a.value = 'a';
	a.left = &b;
	a.right = &c;
	solve_max_distance(&a);
	printf("Ret: %d\n", ret);
}

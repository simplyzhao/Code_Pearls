#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 128 /* maximum number of integers in bst */
typedef void (*operate)(int arg);

struct TNode {
	int value;
	struct TNode *left, *right;
};

void
just_print(int arg)
{
	printf("%d", arg);
}

void
travel_ith_level(struct TNode *root, int level, operate mthd)
{
	if(level == 0) {
		mthd(root->value);
		return;
	}
	if(root->left)
		travel_ith_level(root->left, level-1, mthd);
	if(root->right)
		travel_ith_level(root->right, level-1, mthd);
}

void
travel_level_by_level(struct TNode *root, operate mthd)
{
	if(root == NULL)
		return;
	struct TNode *aux[MAXLEN];
	int i, lbegin, lend, index;
	lbegin = lend = index = 0;
	aux[index++] = root;
	lend = index;
	while(lbegin < lend) {
		for(i=lbegin; i<lend; ++i) {
			mthd(aux[i]->value);
			if(aux[i]->left)
				aux[index++] = aux[i]->left;
			if(aux[i]->right)
				aux[index++] = aux[i]->right;
		}
		printf("\n");
		lbegin = lend;
		lend = index;
	}
}

int
main(int argc, char **argv)
{
	struct TNode a, b, c, d, e, f, g, h, i;
	h.value = 8;
	h.left = h.right = NULL;
	i.value = 9;
	i.left = i.right = NULL;
	f.value = 6;
	f.left = f.right = NULL;
	g.value = 7;
	g.left = g.right = NULL;
	d.value = 4;
	d.left = &h;
	d.right = NULL;
	e.value = 5;
	e.left = NULL;
	e.right = &i;
	b.value = 2;
	b.left = &d;
	b.right = &e;
	c.value = 3;
	c.left = &f;
	c.right = &g;
	a.value = 1;
	a.left = &b;
	a.right = &c;

	travel_level_by_level(&a, just_print);
}

/* binary search tree(static allocation) */
/* 492K 1188MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define MAX_LEN 36
#define MAX_NUM 10007
#define ROOT 1
struct Node {
	char spec[MAX_LEN];
	int count;
	int left, right;
}bst[MAX_NUM];
int cur_index, total;

int
find(int root, char *str)
{
	int ret, parent, cur = root;
	while(cur != 0) {
		parent = cur;
		ret = strcmp(bst[cur].spec, str);
		if(ret == 0) {
			++bst[cur].count;
			return 0;
		} else if(ret < 0) {
			cur = bst[cur].right; 
		} else {
			cur = bst[cur].left;
		}
	}
	return parent;
}

#define ADD(index, str) { \
	strcpy(bst[index].spec, str); \
	bst[index].left = bst[index].right = 0; \
	bst[index].count = 1; \
	++index; }

void
insert(int parent, char *str)
{
	int ret = strcmp(bst[parent].spec, str);
	assert(ret != 0);
	if(ret < 0)
		bst[parent].right = cur_index;
	else 
		bst[parent].left = cur_index;
	ADD(cur_index, str);
}

void
inorder(int index) 
{
	if(index == 0)
		return;
	inorder(bst[index].left);
	printf("%s %.4f\n", bst[index].spec, (bst[index].count*100.0)/total);
	inorder(bst[index].right);
}

int
main(int argc, char **argv)
{
	int parent;
	char str[MAX_LEN];
	total = 1;
	cur_index = ROOT;
	gets(str);
	ADD(cur_index, str); /* create the root node first */
	while(gets(str) != NULL) {
		++total;
		if((parent=find(ROOT, str)) > 0)
			insert(parent, str);
	}
	inorder(ROOT);
}

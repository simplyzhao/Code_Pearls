/*
 * Question:
 * 问题: 给定一个排序数组,如何构造一个二叉排序树
 *
 * Example:
 *
 * Solution:
 * 解法: 选取数组中间的一个元素作为根节点,左边的元素构造左子树,右边的节点构造有子树(递归)
 *
 * See Also:
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101

struct Node {
	int val;
	struct Node *left;
	struct Node *right;
};

struct Node *
create_bst_from_sorted_array(int *arr, int begin, int end)
{
	if(begin > end)
		return NULL;
	int mid = begin + (end-begin)/2;
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	node->val = arr[mid];
	node->left = create_bst_from_sorted_array(arr, begin, mid-1);
	node->right = create_bst_from_sorted_array(arr, mid+1, end);
	return node;
}

void
inorder_print(struct Node *root)
{
	if(root == NULL)
		return;
	inorder_print(root->left);
	printf("%d\t", root->val);
	inorder_print(root->right);
}

void
preorder_print(struct Node *root)
{
	if(root == NULL)
		return;
	printf("%d\t", root->val);
	preorder_print(root->left);
	preorder_print(root->right);
}

int
compare(const void *arg1, const void *arg2)
{
	return (*(int *)arg1) - (*(int *)arg2);
}

int
main(int argc, char **argv)
{
	int i, len, input[MAX_LEN];
	printf("Enter the Length: ");
	scanf("%d", &len);
	for(i=0; i<len; i++) {
		printf("array[%d]=", i);
		scanf("%d", input+i);
	}

	qsort(input, len, sizeof(int), compare);
	struct Node *root = create_bst_from_sorted_array(input, 0, len-1);
	printf("InOrder\n");
	inorder_print(root);
	printf("\n");
	printf("PreOrder\n");
	preorder_print(root);
	printf("\n");
}

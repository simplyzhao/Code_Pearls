#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/*
 * 为了解决RMQ问题我们也可以使用线段树。
 * 线段树是一个类似堆的数据结构，可以在基于区间数组上用对数时间进行更新和查询操作。
 * 我们用下面递归方式来定义线段树的[i, j]区间：
 * 第一个结点将保存区间[i, j]区间的信息
 * 如果i<j 左右的孩子结点将保存区间[i, (i+j)/2]和[(i+j)/2+1, j] 的信息
 * 注意具有N个区间元素的线段树的高度为[logN] + 1。
 */

#define MAX_LEN 30001
#define TREE_MAX_LEN (1<<((int)log(MAX_LEN)+1+1))
#define LEFT(i) ((i)<<1)
#define RIGHT(i) (((i)<<1)+1)

int num[MAX_LEN];
int tr[TREE_MAX_LEN];
int len;

/* build the segment tree */
void
initialize(int node, int begin, int end, int *tree, int *arr)
{
	if(begin == end) {
		tree[node] = begin;
		return;
	}

	int mid = begin + ((end-begin)>>1);
	initialize(LEFT(node), begin, mid, tree, arr);
	initialize(RIGHT(node), mid+1, end, tree, arr);

	tree[node] = arr[tree[LEFT(node)]] <= arr[tree[RIGHT(node)]] ? tree[LEFT(node)] : tree[RIGHT(node)];
}

int
rmq(int node, int begin, int end, int *tree, int *arr, int qb, int qe)
{
	printf("%d - %d : %d - %d\n", begin, end, qb, qe);
	if(begin==qb && end==qe)
		return tree[node];
	
	int mid = begin + ((end-begin)>>1);
	if(qb >= mid+1)
		return rmq(RIGHT(node), mid+1, end, tree, arr, qb, qe);
	if(qe <=mid)
		return rmq(LEFT(node), begin, mid, tree, arr, qb, qe);

	int index1 = rmq(LEFT(node), begin, mid, tree, arr, qb, mid);
	int index2 = rmq(RIGHT(node), mid+1, end, tree, arr, mid+1, qe);

	return arr[index1]<=arr[index2] ? index1 : index2;
}

int
main(int argc, char **argv)
{
	int i;
	scanf("%d", &len);
	for(i=0; i<len; i++)
		scanf("%d", num+i);

	initialize(1, 0, len-1, tr, num);
	int qb, qe, rt;
	while(scanf("%d %d", &qb, &qe) != EOF) {
		rt = rmq(1, 0, len-1, tr, num, qb, qe);
		printf("Index: %d, Value: %d\n", rt, num[rt]);
	}
}

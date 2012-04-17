/*
 * Problem:
 * 有N个人按照1到N编号围成一个圈做游戏,从第一个人开始从1报数,数到M的人退出游戏,他后面的人接着重新从1开始报数,然后一直继续到最后一个人。
 * 输出退出游戏的人的顺序
 *
 * Solution:
 * 模拟(数组 or 链表, 后者更好)
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
int n, m;
struct Item {
	int number;
	struct Item *next;
};

void
solve(int n, int m)
{
	int i, j;
	assert(n>0 && m<=n);
	struct Item *items = (struct Item *)malloc(sizeof(struct Item) * n);
	assert(items != NULL);
	/* init */
	for(i=0; i<n-1; ++i) {
		items[i].number = i+1;
		items[i].next = items+i+1;
	}
	items[n-1].number = n;
	items[n-1].next = items;
	/* simulate */
	struct Item *cur, *prev = NULL;
	cur = items;
	while(n--) {
		j = m;
		while(--j) {
			prev = cur;
			cur = cur->next;
		}
		printf("%d\n", cur->number);
		prev->next = cur->next;
		cur = cur->next;
	}
	free(items);
}

int
main(int argc, char **argv)
{
	while(scanf("%d %d", &n, &m) != EOF) {
		printf("Result of (N=%d, M=%d)\n", n, m);
		solve(n, m);
	}

	return 0;
}

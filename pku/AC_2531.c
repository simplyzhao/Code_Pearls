#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 21
int matrix[MAX_NUM][MAX_NUM];
int mark[MAX_NUM], mark_num;
int num, max;

int
calculate()
{
	int i, j;
	int sum = 0;
	for(i=0; i<num; i++)
		if(mark[i]) {
			for(j=0; j<num; j++)
				if(!mark[j])
					sum += matrix[i][j];
		}
	return sum;
}

void
dfs(int depth)
{
	int rt;
	if(depth == num) {
		rt = calculate();
		max = rt>max ? rt : max;
		return;
	}
	++mark_num;
	mark[depth] = 1; /* mark[depth]=1, put 'depth' into the category I */
	if(mark_num <= (num>>1)) /* pruning */
		dfs(depth+1);
	--mark_num;
	mark[depth] = 0;
	dfs(depth+1); /* put 'depth' into the category II */
}

int
main(int argc, char **argv)
{
	int i, j;
	max = -1;
	memset(mark, 0, sizeof(mark));
	mark_num = 0;
	scanf("%d", &num);
	for(i=0; i<num; i++)
		for(j=0; j<num; j++)
			scanf("%d", &matrix[i][j]);
	dfs(0);
	printf("%d\n", max);
	return 0;
}

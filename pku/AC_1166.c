#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CLK_NUM 9
#define MV_NUM 9
#define DIAL_NUM 4
int clocks[CLK_NUM];
int moves[MV_NUM][CLK_NUM] = {
	{1, 1, 0, 1, 1, 0, 0, 0, 0}, /* move: 1 */
	{1, 1, 1, 0, 0, 0, 0, 0, 0}, /* move: 2 */
	{0, 1, 1, 0, 1, 1, 0, 0, 0}, /* move: 3 */
	{1, 0, 0, 1, 0, 0, 1, 0, 0}, /* move: 4 */
	{0, 1, 0, 1, 1, 1, 0, 1, 0}, /* move: 5 */
	{0, 0, 1, 0, 0, 1, 0, 0, 1}, /* move: 6 */
	{0, 0, 0, 1, 1, 0, 1, 1, 0}, /* move: 7 */
	{0, 0, 0, 0, 0, 0, 1, 1, 1}, /* move: 8 */
	{0, 0, 0, 0, 1, 1, 0, 1, 1}  /* move: 9 */
};
int mv_cur[MV_NUM*4]; /* 4 times a circle for each move */
int mv_cur_num;
int flag;

int 
is_ok()
{
	int i;
	for(i=0; i<CLK_NUM; i++)
		if(clocks[i] % DIAL_NUM != 0)
			return 0;
	return 1;
}

void
dfs(int depth)
{
	if(depth > MV_NUM || flag)
		return;
	int i, j, k;
	if(is_ok()) {
		flag = 1;
		for(i=0; i<mv_cur_num; i++)
			printf("%d ", mv_cur[i]+1);
		printf("\n");
		return;
	}
	for(j=0; j<4; j++) { /* each move test 4 times */
		for(k=0; k<j; k++) {
			for(i=0; i<CLK_NUM; i++)
				clocks[i] += moves[depth][i];
			mv_cur[mv_cur_num] = depth;
			mv_cur_num += 1;
		}
		dfs(depth+1);
		for(k=0; k<j; k++) {
			for(i=0; i<CLK_NUM; i++)
				clocks[i] -= moves[depth][i];
			mv_cur_num -= 1;
		}
	}
}

int
main(int argc, char **argv)
{
	int i;
	memset(mv_cur, 0, sizeof(int)*MV_NUM);
	mv_cur_num = 0;
	flag = 0;
	for(i=0; i<CLK_NUM; i++)
		scanf("%d", clocks+i);

	dfs(0);
	return 0;
}

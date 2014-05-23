/*
 * greedy algorithm
 * 注意：
 * 将输入按照s排序，而不是t，这样才能得到全局最优解...不明白
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 200
struct Move {
	int s;
	int t;
};
int num;
int fin[N];
struct Move tables[N];

int
compare(const void *arg1, const void *arg2)
{
	return ((struct Move *)arg1)->s - ((struct Move *)arg2)->s;
}

int
greedy()
{
	int i, j, s, cur_t, count = 0;
	for(i=0; i<num; i++) {
		if(fin[i] == 0) {
			++count;
			/* greedy */
			fin[i] = 1;
			cur_t = tables[i].t;
			j = i+1;
			while(j < num) {
				s = tables[j].s;
				if(fin[j]==0 && (((s+1)>>1) > ((cur_t+1)>>1))) {
					cur_t = tables[j].t;
					fin[j] = 1;
				}
				++j;
			}
		}
	}
	return count;
}

int
main(int argc, char **argv)
{
	int i, s, t, tests;
	scanf("%d", &tests);
	while(tests--) {
		memset(fin, 0, sizeof(int)*N);
		scanf("%d", &num);
		for(i=0; i<num; i++) {
			scanf("%d %d", &s, &t);
			tables[i].s = s>t ? t : s;
			tables[i].t = s>t ? s : t;
		}
		qsort(tables, num, sizeof(struct Move), compare);
		printf("%d\n", 10*greedy());
	}
	return 0;
}

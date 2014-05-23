#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 7
int target, len;
char num[MAX_LEN];
int sum_count, sum, parts_count, parts[MAX_LEN];
int ans_count, ans[MAX_LEN];

void
dfs(int depth, int cur_sum)
{
	int i, value = 0;
	if(cur_sum > target) /* pruning */
		return;
	if(depth == len) {
		if(cur_sum == sum)
			++sum_count;
		if(cur_sum > sum) {
			sum = cur_sum;
			sum_count = 1;
			ans_count = parts_count;
			memcpy(ans, parts, sizeof(int)*ans_count);
		}
		return;
	}
	for(i=depth; i<len; i++) {
		value *= 10;
		value += (num[i]-'0');
		parts[parts_count++] = value;
		dfs(i+1, cur_sum+value);
		parts[parts_count--] = -1;
	}
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %s", &target, num)!=EOF) {
		if(target == 0)
			break;
		memset(parts, -1, sizeof(parts));
		len = strlen(num);
		sum_count = parts_count = 0;
		sum = -1;
		dfs(0, 0);
		if(sum == -1) {
			printf("error\n");
			continue;
		}
		if(sum_count >= 2) {
			printf("rejected\n");
			continue;
		}
		printf("%d ", sum);
		for(i=0; i<ans_count; i++)
			printf("%d ", ans[i]);
		printf("\n");
	}
}

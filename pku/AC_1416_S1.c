#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 7
int target, num;
int digits_count, digits[MAX_LEN];
int sum_count, sum, parts_count, parts[MAX_LEN];
int ans_count, ans[MAX_LEN];

void
init()
{
	int i, temp, rem;
	memset(digits, -1, sizeof(digits));
	memset(parts, -1, sizeof(parts));
	digits_count = sum_count = parts_count = 0;
	sum = -1;
	rem = num;
	do {
		digits[digits_count++] = rem % 10;
		rem /= 10;
	} while(rem!=0);
	for(i=0; i<digits_count/2; i++) {
		temp = digits[i];
		digits[i] = digits[digits_count-i-1];
		digits[digits_count-i-1] = temp;
	}
}

void
dfs(depth, cur_sum, pre)
{
	if(cur_sum+pre>target) /* pruning */
		return;
	//printf("dfs(%d, %d, %d)\n", depth, cur_sum, pre);
	if(depth == digits_count) {
		if(pre != 0) {
			parts[parts_count++] = pre;
			cur_sum += pre;
		}
		if(cur_sum == sum)
			++sum_count;
		if(cur_sum > sum) {
			sum = cur_sum;
			sum_count = 1;
			ans_count = parts_count;
			memcpy(ans, parts, sizeof(int)*ans_count);
		}
		if(pre != 0)
			parts[parts_count--] = -1;
		return;
	}
	/* branch 1 */
	parts[parts_count++] = digits[depth] + pre * 10;
	dfs(depth+1, cur_sum+parts[parts_count-1], 0);
	parts[parts_count--] = -1;
	/* branch 2 */
	dfs(depth+1, cur_sum, pre*10+digits[depth]);
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %d", &target, &num)!=EOF) {
		if(target==0 && num==0)
			break;
		if(target == num) { /* pruning */
			printf("%d %d\n", target, num);
			continue;
		}
		init();
		dfs(0, 0, 0);
		sum_count = sum_count>>1;
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

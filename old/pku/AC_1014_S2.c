/* DP: 0-1 knapsack */
/* see: http://blog.sina.com.cn/s/blog_5c95cb070100cvt8.html */
/* Tricky 1:
 * for any integer n, we have:
 *   n = 1 + 1<<1 + 1<<2 + 1<<3 + ... + 1<<k + res(余数)
 * And as a result, any integer i from 1 to n, we can say:
 *   i can be represented by 1<<i and res
 *
 * Tricky 2:
 * from Tricky1, the problem can then be considered as a 0-1 knapsack problem.
 * knapsack: value_half/2, cost & value for each one: (1<<i)*value or res*value
 */
/* Memory: 836K Time: 16MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VALUE 6
#define VALUE_HALF_MAX 60005
#define LEN_MAX 150
#define max(a, b) ((a)>(b) ? (a) : (b))
int num[VALUE+1];
int value_weight[LEN_MAX];
int table[2][VALUE_HALF_MAX]; /* just need 2 rows here, memory saving */
int value_sum, value_half;
int len;

int
knapsack()
{
	int i, w, pre, cur;
	memset(table, 0, sizeof(table));
	for(w=value_weight[0]; w<=value_half; w++) {
		table[0][w] = value_weight[0];
		if(table[0][w] == value_half)
			return 1;
	}
	for(i=1; i<len; i++) {
		cur = i%2;
		pre = (i+1)%2;
		for(w=0; w<=value_half; w++) {
			if(w>=value_weight[i])
				table[cur][w] = max(table[pre][w], table[pre][w-value_weight[i]]+value_weight[i]);
			else
				table[cur][w] = table[pre][w];
			if(table[cur][w] == value_half)
				return 1;
		}
	}
	return 0;
}

int
main(int argc, char **argv)
{
	int i, j, tc=0;
	while(1) {
		++tc;
		value_sum = 0;
		for(i=1; i<=VALUE; i++) {
			scanf("%d", num+i);
			value_sum += (i*num[i]);
		}
		if(value_sum == 0)
			break;
		value_half = (value_sum >> 1);
		if(value_sum%2 != 0)
			printf("Collection #%d:\n%s\n\n", tc, "Can't be divided.");
		else {
			len = 0;
			memset(value_weight, 0, sizeof(value_weight));
			for(i=1; i<=VALUE; i++) {
				if(num[i] != 0) {
					j = 0;
					while((1<<(j+1)) <= (num[i]+1)) {
						value_weight[len++] = i*(1<<j);
						++j;
					}
					if((num[i]+1-(1<<j))>0)
						value_weight[len++] = i*(num[i]+1-(1<<j));
				}
			}
			printf("Collection #%d:\n%s\n\n", tc, (knapsack()==1)?"Can be divided.":"Can't be divided.");
		}
	}
}

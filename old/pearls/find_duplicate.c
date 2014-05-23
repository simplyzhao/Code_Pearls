#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* 给定一个长度为N的数组, 其中每个元素的取值范围都是1到N, 判断数组中是否有重复的数字(原数组不必保留) */

/* Solutions:
 * Method 1: Sort; time: O(nlogn) & space: O(1)
 * 
 * Method 2: define an extra array num[N+1], iterate the given array; time: O(n) & space: O(n)
 *
 * Method 3: to reduce the space complexity, each num uses a bit; time: O(n) & O(n)
 *
 * Method 4: 
 * 遍历数组, 假设第i个位置的数字为j, 则通过交换将j换到下标为j的位置上, 直到所有数字都出现在自己对应的下标处, 或发生了冲突
 * 时间复杂度为O(n)[maybe wrong here? O(n^2)], 空间复杂度为O(1)
 */

#define MAX_N 101
#define SET_BIT(ch, index) ((ch) |= (1<<(index)))
#define CLEAR_BIT(ch, index) ((ch) &= (~(1<<(index))))
#define TEST_BIT(ch, index) (((ch) & (1<<(index))) != 0)
int N, input[MAX_N];

int
method_3(int *arr, int len)
{
	int i;
	char bits[MAX_N/8+1] = {0};
	for(i=1; i<=len; i++) {
		if(TEST_BIT(bits[arr[i]/8], (arr[i]%8)-1))
			return 0;
		SET_BIT(bits[arr[i]/8], (arr[i]%8)-1);
	}
	return 1;
}

void
swap(int *arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int
method_4(int *arr, int len)
{
	int i, cur = 1;
	for(i=1; i<=len; i++) {
		while(arr[i] != i) {
			if(arr[i]==arr[arr[i]] || arr[i]<=cur)
				return 0;
			swap(arr, i, arr[i]);
		}
		++cur;
	}
	return 1;
}

int
main(int argc, char **argv)
{
	int i;
	scanf("%d", &N);
	for(i=1; i<=N; i++)
		scanf("%d", input+i);
	printf("%s\n", method_3(input, N) ? "No duplicates" : "duplicates occurred");
	printf("%s\n", method_4(input, N) ? "No duplicates" : "duplicates occurred");
	return 0;
}

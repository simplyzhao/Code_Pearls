/*
 * 给定字符串，求其不出现重复字符的子字符串的最大长度 
 * 比如，“abcabcbb”最大的就是“abc”长度3, “bbbbb”最大就是“b”长度1
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHARACTER_SET 256
#define MAXLEN 128

/*
 * given string S:
 * define f(i) is the length of longest unrepeated substring ended with S[i]
 *     f(i) = f(i-1) + 1, if S[i] hasn't appeared before, or
 *     f(i) = min(i-last[S[i]], f(i-1)+1), last[S[i]] is the most recent appearance index of S[i]
 */
int
solution_dp(const char *str, int len)
{
	int last[CHARACTER_SET], f[MAXLEN], i, ret = 1;
	memset(last, -1, sizeof(last));
	last[str[0]] = 0;
	f[0] = 1;

	for(i=1; i<len; ++i) {
		if(last[str[i]] == -1) { /* hasn't appeared before */
			f[i] = f[i-1] + 1;
			last[str[i]] = i;
		} else { /* appeared before */
			f[i] = i - last[str[i]];
			f[i] = f[i] < f[i-1]+1 ? f[i] : f[i-1]+1;
			last[str[i]] = i;
		}
		ret = ret < f[i] ? f[i] : ret;
	}

	return ret;
}

int
main(int argc, char **argv)
{
	char input[MAXLEN];
	while(scanf("%s", input) != EOF) {
		printf("result of [%s]: %d\n", input, solution_dp(input, strlen(input)));
	}

	return 0;
}

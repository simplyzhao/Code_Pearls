/* high precision */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 150
#define NUM_LEN 6
char str[NUM_LEN+1];
char rt[MAX_LEN];
int n;
int num[NUM_LEN], temp[MAX_LEN], result[MAX_LEN];

void
multiply(int *arg1, int len1, int *arg2, int len2, int *result)
{
	int i, j;
	/* excellent code */
	for(i=0; i<len1; i++) {
		for(j=0; j<len2; j++) {
			result[i+j] += (arg1[i] * arg2[j]);
			result[i+j+1] += (result[i+j] / 10);
			result[i+j] = result[i+j] % 10;
		}
	}
}

int
main(int argc, char **argv)
{
	int i, j, digit, count, left, right;
	while(scanf("%s %d", str, &n) != EOF) {
		memset(num, 0, sizeof(num));
		memset(temp, 0, sizeof(temp));
		memset(result, 0, sizeof(result));
		left = 0;
		while(str[left] == '0')
			++left;
		right = strlen(str)-1;
		while(str[right] == '0')
			--right;
		count = digit = 0;
		for(i=right; i>=left; i--) {
			if(str[i]=='.')
				digit = right - i;
			else
				num[count++] = str[i]-'0';
		}
		memcpy(result, num, count*sizeof(int));
		for(i=1; i<n; i++) {
			memset(temp, 0, sizeof(temp));
			multiply(num, count, result, i*count, temp);
			memcpy(result, temp, (i+1)*count*sizeof(int));
		}
		right = MAX_LEN-1;
		j = 0;
		while(result[right]==0)
			--right;
		if(right < n*digit) {
			rt[j++] = '.';
			right = n*digit - 1;
		}
		for(i=right; i>=0; i--) {
			rt[j++] = result[i]+'0';
			if(digit && (i==n*digit))
				rt[j++] = '.';
		}
		rt[j++] = '\0';
		printf("%s\n", rt);
	}
	return 0;
}

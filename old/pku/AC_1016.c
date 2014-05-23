#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NUM 10 /* 0..9 */
#define UP 15 
#define INPUT_LEN 81
#define MAX_LEN 31
char input[INPUT_LEN], inv[UP][MAX_LEN];
int count[NUM]; 

void
generate(char *src, char *dst)
{
	int i, index, len = strlen(src);
	memset(count, 0, sizeof(count));
	for(i=0; i<len; i++)
		++count[src[i]-'0'];

	index = 0;
	for(i=0; i<NUM; i++) {
		if(count[i] > 0) {
			if(count[i] >= 10) {
				dst[index++] = (count[i]/10)+'0';
				dst[index++] = (count[i]%10)+'0';
			} else {
				dst[index++] = count[i]+'0';
			}
			dst[index++] = i+'0';
		}
	}
}

void
solve()
{
	int i, index = 0;
	generate(input, inv[index]);
	if(strcmp(input, inv[index]) == 0) {
		printf("%s is self-inventorying\n", input);
		return;
	}
	++index;
	while(index < UP) {
		generate(inv[index-1], inv[index]);
		if(strcmp(inv[index], inv[index-1]) == 0) {
			printf("%s is self-inventorying after %d steps\n", input, index);
			return;
		}
		for(i=index-2; i>=0; i--)
			if(strcmp(inv[index], inv[i]) == 0) {
				printf("%s enters an inventory loop of length %d\n", input, index-i);
				return;
			}
		if(index >= 1)
			if(strcmp(inv[index], input) == 0) {
				printf("%s enters an inventory loop of length %d\n", input, index+1);
				return;
			}
		++index;
	}
	printf("%s can not be classified after 15 iterations\n", input);
}

int
main(int argc, char **argv)
{
	while(scanf("%s", input) != EOF) {
		if(strcmp(input, "-1") == 0)
			break;
		memset(inv, 0, sizeof(inv));
		solve();
	}
}

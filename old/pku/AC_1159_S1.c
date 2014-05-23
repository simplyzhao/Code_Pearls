/* Time: 1594MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 5001
char str[MAX_LEN+1];
int len;
short memory[MAX_LEN][MAX_LEN];

/*
 * f[i][j] represent the minimal insert for str[i..j]
 *
 * f[i][j] = f[i+1][j-1], if str[i]==str[j], otherwise
 * f[i][j] = min(f[i+1][j], f[i][j-1]) + 1
 */
int
func(int i, int j)
{
	int a, b;
	if(i >= j)
		return 0;
	if(memory[i][j])
		return memory[i][j];
	if(str[i] == str[j])
		memory[i][j] = func(i+1, j-1);
	else {
		a = func(i+1, j);
		b = func(i, j-1);
		memory[i][j] = a<b ? a+1 : b+1;
	}
	return memory[i][j];
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &len) != EOF) {
		memset(memory, 0, sizeof(memory));
		scanf("%s", str+1);
		printf("%d\n", func(1, len));
	}
}

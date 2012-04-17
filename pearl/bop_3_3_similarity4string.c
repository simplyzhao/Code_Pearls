/*
 * Problem:
 * similarity = 1 / steps_of_operations
 * operation:
 *     a. modify a character
 *     b. add a character
 *     c. delete a character
 * steps_of_operations = smallest number of operations needed turning string A to B
 *
 * Solution:
 * dynamic programming
 * define f[i][j] as the number of operations needed turning A[1..i] to B[1..j], we have:
 *    f[i][j] = f[i-1[j-1] if A[i] = B[j]
 *    f[i][j] = min(f[i-1][j], f[i][j-1], f[i-1][j-1])+1, if A[i] != B[j]
 *
 * From: BOP 3.3
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 1001
char str1[MAXLEN+1], str2[MAXLEN+1];
int len1, len2;
int table[MAXLEN][MAXLEN];

void
dp()
{
	int i, j, min;
	/* init */
	for(j=0; j<=len2; ++j)
		table[0][j] = j;
	for(i=0; i<=len1; ++i)
		table[i][0] = i;

	/* dp */
	for(i=1; i<=len1; ++i) {
		for(j=1; j<=len2; ++j) {
			if(str1[i] == str2[j])
				table[i][j] = table[i-1][j-1];
			else {
				min = table[i-1][j] < table[i][j-1] ? table[i-1][j] : table[i][j-1];
				min = min < table[i-1][j-1] ? min : table[i-1][j-1];
				table[i][j] = min+1;
			}
		}
	}
}

int
main(int argc, char **argv)
{
	while(scanf("%s %s", str1+1, str2+1) != EOF) {
		len1 = strlen(str1+1);
		len2 = strlen(str2+1);
		memset(table, 0, sizeof(table));

		dp();
		fprintf(stdout, "Number of Operations: %d\n", table[len1][len2]);
	}
}

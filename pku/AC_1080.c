#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101
#define INF 'I'
#define Score(ch_a, ch_b) (score[map[ch_a-'A']][map[ch_b-'A']])
int len_a, len_b;
char str_a[MAX_LEN+1], str_b[MAX_LEN+1];
int table[MAX_LEN][MAX_LEN];
const int score[][5] = {{5,-1,-2,-1,-3}, {-1,5,-3,-2,-4}, {-2,-3,5,-2,-2}, {-1,-2,-2,5,-1}, {-3,-4,-2,-1,-65535}};
                /* A    C          G    I                               T */  
const int map[] = {0,-1,1,-1,-1,-1,2,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3};

/*
 * f[i][j] represent the similarity of str_a[1..i] and str_b[1..j], so:
 *    f[i][j] = max { f[i-1][j-1]+Score(str_a[i], str_b[j]), 
 *                    f[i-1][j] + Score(str_a[i], '-'),
 *                    f[i][j-1] + Score('-', str_b[j]) }
 */
int
dp()
{
	int i, j, a, b, c, max;
	/* Attention: Initialization */
	table[0][0] = 0;
	for(i=1; i<=len_a; i++)
		table[i][0] = table[i-1][0] + Score(str_a[i], INF);
	for(j=1; j<=len_b; j++)
		table[0][j] = table[0][j-1] + Score(str_b[j], INF);
	
	for(i=1; i<=len_a; i++) {
		for(j=1; j<=len_b; j++) {
			a = table[i-1][j-1] + Score(str_a[i], str_b[j]);
			b = table[i-1][j] + Score(str_a[i], INF);
			c = table[i][j-1] + Score(INF, str_b[j]);
			max = a > b ? a : b;
			max = c > max ? c : max;
			table[i][j] = max;
		}
	}
	return table[len_a][len_b];
}

int
main(int argc, char **argv)
{
	int tests;
	scanf("%d", &tests);
	while(tests--) {
		scanf("%d %s", &len_a, str_a+1);
		scanf("%d %s", &len_b, str_b+1);
		printf("%d\n", dp());
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 45
int zero_end[MAX_LEN+1];
int one_end[MAX_LEN+1];

int
build_table()
{
	int i;
	zero_end[1] = 1;
	one_end[1] = 1;
	for(i=2; i<=45; i++) {
		zero_end[i] = zero_end[i-1] + one_end[i-1];
		one_end[i] = zero_end[i-1];
	}
}

int
main(int argc, char **argv)
{
	int i, n, tests;
	build_table();
	scanf("%d", &tests);
	for(i=1; i<=tests; i++) {
		scanf("%d", &n);
		printf("Scenario #%d:\n%d\n\n", i, zero_end[n]+one_end[n]);
	}
}

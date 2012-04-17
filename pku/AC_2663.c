#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 31
long table[MAX_LEN];

void
build_table()
{
	int i, j, sum;
	memset(table, 0, sizeof(table));
	table[0] = 1;
	table[2] = 3;
	for(i=4; i<MAX_LEN; i=i+2) {
		sum = 3*table[i-2];
		for(j=4; i-j>=0; j=j+2)
			sum += (table[i-j]<<1);
		table[i] = sum;
	}
}

int
main(int argc, char **argv)
{
	int n;
	build_table();
	while(scanf("%d", &n)!=EOF && n!=-1) {
		printf("%ld\n", table[n]);
	}
}

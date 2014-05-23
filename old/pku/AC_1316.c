#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 10001
#define DIV 10
int mark[MAX_LEN];

int
generate(int generator)
{
	int sum = generator;
	while(generator > 0) {
		sum += (generator % 10);
		generator /= DIV;
	}
	return sum;
}

int
main(int argc, char **argv)
{
	int i, k;
	for(i=1; i<MAX_LEN; i++)
		if((k=generate(i)) < MAX_LEN)
			mark[k] = 1;
	for(i=1; i<MAX_LEN; i++)
		if(!mark[i])
			printf("%d\n", i);
}

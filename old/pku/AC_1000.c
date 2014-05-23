#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int
main(int argc, char **argv)
{
	int a, b;
	while(scanf("%d %d", &a, &b)!=EOF)
		printf("%d\n", a+b);
}

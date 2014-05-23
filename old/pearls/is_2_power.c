#include<stdio.h>

int is_2_power(int n)
{
	if((n&(n-1)) == 0)
		return 1;
	else
		return 0;
}

int main(int argc, char **argv)
{
	int num;
	scanf("%d", &num);
	printf(is_2_power(num)?"yes":"no");
	printf("\n");
	return 0;
}

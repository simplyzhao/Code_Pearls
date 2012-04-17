/*
 * Problem:
 * Greatest Common Divisor (gcd)
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int
gcd(int a, int b)
{
	int temp;
	while(b) {
		temp = b;
		b = a%b;
		a = temp;
	}
	return a;
}

int
rgcd(int a, int b)
{
	if(b)
		return rgcd(b, a%b);
	return a;
}

int
main(int argc, char **argv)
{
	int a, b;
	printf("Greatest Common Divisor\n");
	printf("Enter two numbers: ");
	scanf("%d %d", &a, &b);
	printf("gcd: %d(gcd method), %d(rgcd method)\n", gcd(a, b), rgcd(a, b));
}

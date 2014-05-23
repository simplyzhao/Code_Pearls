/* water */
#include<stdio.h>

int 
main(int argc, char **argv)
{
	float c, cur;
	int n;
	while(scanf("%f", &c) && c!=0.00) {
		n = 2;
		cur = (1.0)/n;
		while(cur < c)
			cur += (1.0)/(++n);
		printf("%d card(s)\n", n-1);
	}
}

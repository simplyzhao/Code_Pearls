/* water */
/* except the format of printf: 宽度.精度 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MONTHS 12
int
main(int argc, char **argv)
{
	int i;
	float m, sum = 0;
	for(i=0; i<MONTHS; i++) {
		scanf("%f", &m);
		sum += m;
	}
	printf("$%02.2f\n", sum/MONTHS);
}

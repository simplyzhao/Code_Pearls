#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PI 3.14
double distance;

int
is_within(double area)
{
	if(area/PI >= distance)
		return 1;
	return 0;
}

int
main(int argc, char **argv)
{
	int i, tests, year;
    float x, y;
	double area;
	scanf("%d", &tests);
	for(i=1; i<=tests; i++) {
		year = 0;
		area = 0;
		scanf("%f %f", &x, &y);
		distance = x*x+y*y;
		do {
			++year;
			area += 100;
		} while(!is_within(area));
		printf("Property %d: This property will begin eroding in year %d.\n", i, year);
	}
	printf("END OF OUTPUT.\n");
}

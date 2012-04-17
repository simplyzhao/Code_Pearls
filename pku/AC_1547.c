#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NAME_LEN 9
#define MAX_STU 9
int num, cubics[MAX_STU];
char name[MAX_STU][MAX_NAME_LEN];

int
main(int argc, char **argv)
{
	int i, sum, avg, a, b, c, bully, victim;
	while(scanf("%d", &num)!=EOF && num!=-1) {
		sum = 0;
		for(i=0; i<num; i++) {
			scanf("%d %d %d %s", &a, &b, &c, name[i]);
			cubics[i] = a*b*c;
			sum += cubics[i];
		}
		avg = sum/num;
		for(i=0; i<num; i++) {
			if(cubics[i] < avg)
				victim = i;
			else if(cubics[i] > avg)
				bully = i;
		}
		printf("%s took clay from %s.\n", name[bully], name[victim]);
	}
}

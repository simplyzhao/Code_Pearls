/* 35640K 1844MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 36
#define MAX_NUM 1000001
char species[MAX_NUM][MAX_LEN];

int
cmp(const void *arg1, const void *arg2)
{
	return strcmp((char *)arg1, (char *)arg2);
}

int
main(int argc, char **argv)
{
	int i, count, total = 0;
	while(gets(species[total]) != NULL)
		++total;
	qsort(species, total, sizeof(species[0]), cmp);
	count = 1;
	for(i=1; i<total; i++) {
		if(strcmp(species[i], species[i-1]) == 0) 
			++count;
		else {
			printf("%s %.4f\n", species[i-1], (count*100.0)/total);
			count = 1;
		}
	}
	printf("%s %.4f\n", species[total-1], (count*100.0)/total);
}

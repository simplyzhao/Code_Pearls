#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 16
int num[MAX_LEN];
int n, total;

int
compare(const void *arg1, const void *arg2)
{
	return *((int *)arg1) - *((int *)arg2);
}

int
main(int argc, char **argv)
{
	int i, tmp;
	while(scanf("%d", num) && num[0] != -1) {
		total = 0;
		n = 1;
		while(scanf("%d", num+n) && num[n] != 0)
			++n;
		qsort(num, n, sizeof(int), compare);
		for(i=0; i<n; i++) {
			tmp = (num[i]) << 1;
			if(bsearch(&tmp, num, n, sizeof(int), compare) != NULL)
				++total;
		}
		printf("%d\n", total);
	}
}

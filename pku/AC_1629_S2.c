#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101
#define ALPHA 26
char temp[MAX_LEN];
int counts[ALPHA];

int
main(int argc, char **argv)
{
	int i, j, len;
	int n, m, p;
	memset(counts, 0, sizeof(counts));
	scanf("%d %d %d", &n, &m, &p);
	for(i=0; i<n; i++) {
		scanf("%s", temp);
		len = strlen(temp);
		for(j=0; j<len; j++)
			++counts[temp[j]-'A'];
	}
	for(i=0; i<p; i++) {
		scanf("%s", temp);
		len = strlen(temp);
		for(j=0; j<len; j++)
			--counts[temp[j]-'A'];
	}
	for(i=0; i<ALPHA; i++) {
		if(counts[i])
			for(j=0; j<counts[i]; j++)
				printf("%c", i+'A');
	}
	printf("\n");
}

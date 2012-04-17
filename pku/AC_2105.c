#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 32
const int num[] = {1, 2, 4, 8, 16, 32, 64, 128};
char seq[MAX_LEN+1];

int
main(int argc, char **argv)
{
	int i, j, sum, tests;
	scanf("%d", &tests);
	while(tests--) {
		scanf("%s", seq);
		for(i=0; i<4; i++) {
			sum = 0;
			for(j=(i+1)*8-1; j>=i*8; j--)
				if(seq[j] == '1')
					sum += num[8-(j%8)-1];
			printf("%d", sum);
			if(i != 3)
				printf(".");
		}
		printf("\n");
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_NUM 101
long table[MAX_NUM]; /* preprocess */

int
main(int argc, char **argv)
{
	int i, a, b, c, d;
	int upper;
	scanf("%d", &upper);
	for(i=0; i<=upper; i++) 
		table[i] = pow(i, 3);
	for(a=6; a<=upper; a++) {
		for(b=2; b<upper; b++) {
			for(c=b+1; c<upper; c++) {
				for(d=c+1; d<upper; d++) {
					if(table[a] == (table[b]+table[c]+table[d]))
						printf("Cube = %d, Triple = (%d,%d,%d)\n", a, b, c, d);
				}
			}
		}
	}
	return 0;
}

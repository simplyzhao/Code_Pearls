#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 10
int n;
char str[MAX_LEN];
const int mark[5][10][3] = {
/*    0      1      2      3      4      5      6      7      8      9    */
    0,1,0, 0,0,0, 0,1,0, 0,1,0, 0,0,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0,
    1,0,1, 0,0,1, 0,0,1, 0,0,1, 1,0,1, 1,0,0, 1,0,0, 0,0,1, 1,0,1, 1,0,1,
    0,0,0, 0,0,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,0,0, 0,1,0, 0,1,0,
    1,0,1, 0,0,1, 1,0,0, 0,0,1, 0,0,1, 0,0,1, 1,0,1, 0,0,1, 1,0,1, 0,0,1,
    0,1,0, 0,0,0, 0,1,0, 0,1,0, 0,0,0, 0,1,0, 0,1,0, 0,0,0, 0,1,0, 0,1,0 };

int
main(int argc, char **argv)
{
	int j, k, p, q, w;
	while(scanf("%d %s", &n, str) != EOF) {
		if(!n)
			break;
		for(j=0; j<5; j++) {
			if(j%2 == 0) {
				for(p=0; str[p]!='\0'; p++) {
					printf(" "); /* mark[j][k][0] */
					k = str[p] - '0';
					for(q=0; q<n; q++) 
						printf("%s", mark[j][k][1]?"-":" ");
					printf(" "); /* mark[j][k][2] */
					printf(" ");
				}
				printf("\n");
			} else {
				for(q=0; q<n; q++) {
					for(p=0; str[p]!='\0'; p++) {
						k = str[p] - '0';
						printf("%s", mark[j][k][0]?"|":" ");
						for(w=0; w<n; w++)
							printf(" ");
						printf("%s", mark[j][k][2]?"|":" ");
						printf(" ");
					}
					printf("\n");
				}
			}
		}
		printf("\n");
	}
	return 0;
}

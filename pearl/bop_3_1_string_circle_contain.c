/*
 * Problem:
 *    given string A and B, tell whether if B contained by A or rotated-A
 *
 * Example:
 *	  A = "abcd", B="cda"
 *	  true, because rotated-A = {"abcd", "bcda", "cdab, "dabc"}
 *
 * From: BOP 3.1
 */
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 100
char A[MAXLEN+1];
char B[MAXLEN+1];
char aux[MAXLEN*2+1];

int
main(int argc, char **argv)
{
	while(scanf("%s %s", A, B) != EOF) {
		strcpy(aux, A);
		strcat(aux, A);

		if(strstr(aux, B) != NULL)
			printf("true\n");
		else
			printf("false\n");
	}
}

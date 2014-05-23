#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 256
char str[MAX_LEN];

int
main(int argc, char **argv)
{
	int i, len, total;
	while(gets(str)!=NULL && str[0]!='#') {
		total = 0;
		len = strlen(str);
		for(i=0; i<len; i++)
			if(str[i]>='A' && str[i]<='Z')
				total += ((i+1)*(str[i]-'A'+1));
		printf("%d\n", total);
	}
}

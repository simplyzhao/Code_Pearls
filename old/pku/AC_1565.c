#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 45
int
main(int argc, char **argv)
{
	int i, digit, len, bit;
    char input[MAX_LEN];
	long sum;
	while(scanf("%s", input)!=EOF) {
		if(strcmp(input, "0")==0)
			break;
		sum = 0;
		len = strlen(input);
		for(i=0; i<len; i++) {
			digit = input[i]-'0';
			bit = len - i;
			sum += (long)(digit * ((long)(1<<bit)-1));
		}
		printf("%ld\n", sum);
	}
}

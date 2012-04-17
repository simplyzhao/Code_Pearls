#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 2500
char num[MAX_LEN];

void
digital_root(int num)
{
	int sum = 0;
	while(num > 0) {
		sum += (num%10);
		num /= 10;
	}
	if(sum >= 10)
		digital_root(sum);
	else
		printf("%d\n", sum);
}

int
main(int argc, char **argv)
{
	int i, t, len;
	while(scanf("%s", num)!=EOF && num[0]!='0') {
		t = 0;
		len = strlen(num);
		for(i=0; i<len; i++)
			t += (num[i]-'0');
		digital_root(t);
	}
}

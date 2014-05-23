#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ENDALL "ENDOFINPUT"
#define MAX_LEN 250
const char cipher[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char plain[] =  "VWXYZABCDEFGHIJKLMNOPQRSTU";
char msg[MAX_LEN];

void
translate(char *msg)
{
	int i, len=strlen(msg);
	for(i=0; i<len; i++)
		if(msg[i]>='A' && msg[i]<='Z')
			msg[i] = plain[msg[i]-'A'];
	printf("%s\n", msg);
}

int
main(int argc, char **argv)
{
	char temp[15];
	while(gets(temp)!=EOF) {
		if(strcmp(temp, ENDALL)==0)
			break;
		gets(msg);
		translate(msg);
		gets(temp);
	}
	return 0;
}

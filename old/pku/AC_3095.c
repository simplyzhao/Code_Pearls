#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 80
char seq[MAX_LEN];
int len, total;

int
mountain(int pos, int dir)
{
	int i = pos+dir;
	while(i>=0 && i<len) {
		if(seq[i] == '_')
			i += dir;
		else if(seq[i] == '.')
			return 1;
		else if(seq[i]=='|' || seq[i]=='/' || seq[i]=='\\')
			return 0;
	}
	return 1;
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%s", seq)!=EOF && seq[0]!='#') {
		total = 0;
		len = strlen(seq);
		for(i=0; i<len; i++) {
			switch(seq[i]) {
				case '.':
					total += 100;
					break;
				case '_':
					break;
				case '/':
					total += (mountain(i, -1)*100);
					break;
				case '\\':
					total += (mountain(i, 1)*100);
					break;
				case '|':
					total += ((mountain(i, -1)+mountain(i, 1))*50);
					break;
			}
		}
		printf("%d\n", total/len);
	}
}

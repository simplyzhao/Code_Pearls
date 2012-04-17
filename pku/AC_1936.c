#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 100001
char sub[MAX_LEN], seq[MAX_LEN];
int sub_len, seq_len;

int
main(int argc, char **argv)
{
	char *sub_p, *seq_p;
	while(scanf("%s %s", sub, seq) != EOF) {
		sub_len = strlen(sub);
		seq_len = strlen(seq);
		for(sub_p=sub, seq_p=seq; sub_p<sub+sub_len && seq_p<seq+seq_len; )
			if(*sub_p == *seq_p) {
				++sub_p;
				++seq_p;
			} else
				++seq_p;
		if(sub_p == sub+sub_len)
			printf("Yes\n");
		else
			printf("No\n");
	}
}

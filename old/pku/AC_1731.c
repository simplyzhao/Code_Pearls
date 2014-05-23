/* 364K 454MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 201
char str[MAX_LEN];
int len;

int
compare(const void *arg1, const void *arg2) /* for qsort */
{
	return *((char *)arg1) - *((char *)arg2);
}

void
swap(char *seq, int i, int j) /* exchange */
{
	char tmp = seq[i];
	seq[i] = seq[j];
	seq[j] = tmp;
}

void
perm(char *seq, int begin, int end)
{
	int i, j, tmp;
	char pre=0;
	if(begin >= end) {
		printf("%s\n", seq);
		return;
	}
	for(i=begin; i<=end; i++) {
		if(i>begin && seq[i]==seq[begin]) /* avoid duplicates */
			continue;
		if(pre == seq[i]) /* avoid duplicate */
			continue;
		/* in order to keep the alphabetical order */
		tmp = seq[i];
		for(j=i; j>begin; j--)
			seq[j] = seq[j-1];
		seq[begin] = tmp;
		perm(seq, begin+1, end);
		tmp = seq[begin];
		for(j=begin; j<i; j++)
			seq[j] = seq[j+1];
		seq[i] = tmp;
		/*
		swap(seq, begin, i);
		perm(seq, begin+1, end);
		swap(seq, begin, i);
		*/
		pre = seq[i];
	}
}

int
main(int argc, char **argv)
{
	while(scanf("%s", str) != EOF) {
		len = strlen(str);
		qsort(str, len, sizeof(char), compare);
		perm(str, 0, len-1);
	}
}

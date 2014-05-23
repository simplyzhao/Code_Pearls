#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 1
#define MAXN 5000000
char buf[MAXN], *suffix[MAXN];

int
compare(const void *arg1, const void *arg2)
{
	return strcmp(*(char **)arg1, *(char **)arg2);
}

int
comlen(char *p, char *q)
{
	int count = 0;
	while(*p && (*p++ == *q++))
		++count;
	return count;
}

int
main(int argc, char **argv)
{
	int ch, n = 0;
	while((ch=getchar()) != EOF) {
		getchar();
		buf[n] = ch;
		suffix[n] = buf + n;
		++n;
	}
	buf[n] = 0;

	qsort(suffix, n, sizeof(char *), compare);

	int i, ret, max_i, max_len = -1;
	for(i=0; i<n-M; i++) {
		ret = comlen(suffix[i], suffix[i+M]);
		if(ret > max_len) {
			max_len = ret;
			max_i = i;
		}
	}

	printf("Longest Duplicates: %.*s\n", max_len, suffix[max_i]);

	return 0;
}

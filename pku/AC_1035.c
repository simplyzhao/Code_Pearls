#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 16
#define MAX_NUM 10003
typedef struct _Words {
	char word[MAX_LEN];
	int len;
}Words;
Words words[MAX_NUM], sorted[MAX_NUM];
int total_words;

int
cmp(const void *arg1, const void *arg2)
{
	return strcmp(((Words *)arg1)->word, ((Words *)arg2)->word);
}

int
is_within(const char *word, const char *ctx)
{
	const char *pw = word;
	const char *pc = ctx;
	while((*pw!='\0') && (*pc!='\0')) {
		if(*pw == *pc)
			++pw;
		++pc;
	}
	return (*pw=='\0');
}

int
is_replace(const char *word, const char *ctx)
{
	const char *pw = word;
	const char *pc = ctx;
	int diff = 0;
	while((*pw)!='\0' && (*pc)!='\0') {
		if(*pw != *pc)
			++diff;
		++pw;
		++pc;
	}
	return diff==1;
}

void
solve(char *test)
{
	int i, len = strlen(test);
	Words tmp;
	strcpy(tmp.word, test);
	if(bsearch(&tmp, sorted, total_words, sizeof(Words), cmp) != NULL) {
		printf("%s is correct\n", test);
		return;
	}
	printf("%s: ", test);
	for(i=0; i<total_words; i++) {
		if(words[i].len>len+1 || len>words[i].len+1)
			continue;
		if(words[i].len == len+1) {
			if(is_within(test, words[i].word))
				printf("%s ", words[i].word);
		} else if(words[i].len+1 == len) {
			if(is_within(words[i].word, test))
				printf("%s ", words[i].word);
		} else {
			if(is_replace(words[i].word, test))
				printf("%s ", words[i].word);
		}
	}
	printf("\n");
}

int
main(int argc, char **argv)
{
	total_words = 0;
	char tst[MAX_LEN];
	while(scanf("%s", words[total_words].word)!=EOF && words[total_words].word[0]!='#') {
		words[total_words].len = strlen(words[total_words].word);
		++total_words;
	}
	memcpy(sorted, words, sizeof(Words)*total_words);
	qsort(sorted, total_words, sizeof(Words), cmp);

	while(scanf("%s", tst)!=EOF && tst[0]!='#') 
		solve(tst);
}

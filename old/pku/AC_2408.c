/* 47MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 30001
#define MAX_LEN 36
#define MAX_OUT 5
struct Word {
	char word[MAX_LEN];
	char word_cmp[MAX_LEN];
} words[MAX_NUM];

struct Summary {
	struct Word *first;
	int count;
} smmry[MAX_NUM];

int total, total_category;

int
cmp_char(const void *arg1, const void *arg2)
{
	return (*(char *)arg1) - (*(char *)arg2);
}

int
cmp_words(const void *arg1, const void *arg2)
{
	int ret = strcmp(((struct Word *)arg1)->word_cmp, ((struct Word *)arg2)->word_cmp);
	if(ret == 0)
		ret = strcmp(((struct Word *)arg1)->word, ((struct Word *)arg2)->word);
	return ret;
}

int
cmp_category(const void *arg1, const void *arg2)
{
	int ret = ((struct Summary *)arg2)->count - ((struct Summary *)arg1)->count;
	if(ret == 0)
		ret = strcmp(((struct Summary *)arg1)->first->word, ((struct Summary *)arg2)->first->word);
	return ret;
}

int
main(int argc, char **argv)
{
	int i, j, num, len;
	total = total_category = 0;
	while(scanf("%s", words[total].word) != EOF) {
		len = strlen(words[total].word);
		strcpy(words[total].word_cmp, words[total].word);
		qsort(words[total].word_cmp, len, sizeof(char), cmp_char); 
		++total;
	}
	qsort(words, total, sizeof(struct Word), cmp_words);

	num = 1;
	for(i=1; i<total; i++) {
		if(strcmp(words[i].word_cmp, words[i-1].word_cmp) == 0)
			++num;
		else {
			smmry[total_category].first = words+i-num;
			smmry[total_category].count = num;
			++total_category;
			num = 1;
		}
	}
	smmry[total_category].first = words+i-num;
	smmry[total_category++].count = num;
	qsort(smmry, total_category, sizeof(struct Summary), cmp_category);

	total_category = total_category < MAX_OUT ? total_category : MAX_OUT;
	for(i=0; i<total_category; i++) {
		printf("Group of size %d: %s ", smmry[i].count, smmry[i].first->word);
		for(j=1; j<smmry[i].count; j++)
			if(strcmp((smmry[i].first+j)->word, (smmry[i].first+j-1)->word) != 0)
				printf("%s ", (smmry[i].first+j)->word);
		printf(".\n");
	}
}

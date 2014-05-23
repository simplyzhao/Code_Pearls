#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_WORD_LEN 10001
#define MAX_TEXT_LEN 1000001
char word[MAX_WORD_LEN+1];
char text[MAX_TEXT_LEN+1];
int word_len, text_len, count, next[MAX_WORD_LEN+1];

void
init()
{
	scanf("%s", word+1);
	scanf("%s", text+1);
	word_len = strlen(word+1);
	text_len = strlen(text+1);
	count = 0;
}

void
get_next()
{
	int i, j=0;
	next[1] = 0;
	for(i=2; i<=word_len; i++) {
		while(j>0 && word[j+1]!=word[i])
			j = next[j];
		if(word[j+1] == word[i])
			++j;
		next[i] = j;
	}
}

void
kmp()
{
	int i, j=0;
	for(i=1; i<=text_len; i++) {
		while(j>0 && text[i]!=word[j+1])
			j = next[j];
		if(text[i] == word[j+1])
			++j;
		if(j == word_len) {
			++count;
			j = next[j];
		}
	}
}

int
main(int argc, char **argv)
{
	int tests;
	scanf("%d", &tests);
	while(tests--) {
		init();
		get_next();
		kmp();
		printf("%d\n", count);
	}
}

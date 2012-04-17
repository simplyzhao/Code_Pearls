/*
 * Problem:
 *   Separate the token from given text, for example:
 *   /usr/bin/ : /usr/local/bin : /home/joey/bin
 *
 * Point:
 * Finite AutoMachine is a powerful tool for text manipulation
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define IS_DELIM(c, delims) (strchr(delims, c) != NULL)
typedef void (*OnTokenFunc)(void *ctx, int index, const char *token);
enum _State {
	STAT_IN,
	STAT_OUT,
	STAT_INIT
} state = STAT_INIT;

int
parse_token(const char *text, const char *delims, OnTokenFunc on_token, void *ctx)
{
	int count = 0;
	char *copy_text = strdup(text);
	char *ptr, *token = copy_text;
	for(ptr=copy_text; *ptr!='\0'; ptr++) {
		switch(state) {
			case STAT_INIT:
			case STAT_OUT:
				if(!IS_DELIM(*ptr, delims)) {
					token = ptr;
					state = STAT_IN;
				}
				break;
			case STAT_IN:
				if(IS_DELIM(*ptr, delims)) {
					*ptr = '\0';
					on_token(ctx, count++, token);
					state = STAT_OUT;
				}
				break;
			default:
				break;
		}
	}
	if(state == STAT_IN)
		on_token(ctx, count++, token);
	free(copy_text);
	return count;
}


/* ------------------------- TEST ------------------------------ */
void
token_print(void *ctx, int index, const char *token)
{
	printf("Token %d: %s\n", index, token);
	return;
}

int
main(int argc, char **argv)
{
	char text[100], delims[10];
	scanf("%s %s", text, delims);
	parse_token(text, delims, token_print, NULL);
}

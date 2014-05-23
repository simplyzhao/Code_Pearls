#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 60
char first[MAX_LEN], second[MAX_LEN];
int first_hash[26], second_hash[26]; /* a-z */

int
solve()
{
	int i, len, rt = 0;
	len = strlen(first);
	for(i=0; i<len; i++)
		++first_hash[first[i]-'a'];
	len = strlen(second);
	for(i=0; i<len; i++)
		++second_hash[second[i]-'a'];
	for(i=0; i<26; i++)
		rt += (first_hash[i]-second_hash[i]>0 ? first_hash[i]-second_hash[i] : second_hash[i]-first_hash[i]);
	return rt;
}

int
main(int argc, char **argv)
{
	int i, total;
	scanf("%d", &total);
	getchar();
	for(i=1; i<=total; i++) {
		/* scanf("%s %s", first, second); */
		gets(first);
		gets(second);
		memset(first_hash, 0, sizeof(first_hash));
		memset(second_hash, 0, sizeof(second_hash));
		printf("Case #%d:  %d\n", i, solve());
	}
}

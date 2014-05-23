#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * Example:
 * Input: hi I am Alex.Zhao
 * Output: Alex.Zhao am I hi
 */

void
word_reverse(char *input, char *output) /* bad: extra room to store the result */
{
	int i, innerlen, len = strlen(input);
	int index = 0;

	for(i=len-1; i>=0; --i) {
		if(input[i] == ' ') {
			innerlen = strlen(input+i+1);
			strcpy(output+index, input+i+1);
			index += innerlen;
			output[index++] = ' ';
			input[i] = '\0';
		}
	}
	strcpy(output+index, input);
	index += strlen(input);
	output[index] = '\0';
}

void 
word_reverse_better(char *input)
{
	/* Example:
	 * first reverse the all input
	 * second reverse each word
	 */
}

int
main(int argc, char **argv)
{
	char input[] = "hi I am Alex.Zhao";
	char output[100];
	word_reverse(input, output);
	printf("%s\n", output);
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 101
#define MAX_LEN 31
char first[MAX_NUM][MAX_LEN];
char second[MAX_NUM][MAX_LEN];
int fcnt, scnt;
int table[MAX_NUM][MAX_NUM];
char path[MAX_NUM][MAX_NUM];

void
output(int i, int j)
{
	if(i==0 || j==0)
		return;
	if(path[i][j] == 'u')
		output(i-1, j);
	else if(path[i][j] == 'l')
		output(i, j-1);
	else {
		output(i-1, j-1);
		printf("%s ", first[i-1]);
	}
}

void
lcs()
{
	int i, j;
	for(i=0; i<=fcnt; i++)
		table[i][0] = 0;
	for(j=0; j<=scnt; j++)
		table[0][j] = 0;
	for(i=1; i<=fcnt; i++) {
		for(j=1; j<=scnt; j++) {
			if(strcmp(first[i-1], second[j-1]) == 0) {
				table[i][j] = table[i-1][j-1] + 1;
				path[i][j] = 'y';
			} else if(table[i-1][j] > table[i][j-1]) {
				table[i][j] = table[i-1][j];
				path[i][j] = 'u';
			} else {
				table[i][j] = table[i][j-1];
				path[i][j] = 'l';
			}
		}
	}
}

int
main(int argc, char **argv)
{
	while(1) {
		fcnt = scnt = 0;
		memset(table, 0, sizeof(table));
		memset(path, 0, sizeof(path));
		if(scanf("%s", first[fcnt++]) == EOF)
			break;
		while(scanf("%s", first[fcnt]) && first[fcnt][0]!='#')
			++fcnt;
		while(scanf("%s", second[scnt]) && second[scnt][0]!='#')
			++scnt;
		lcs();
		output(fcnt, scnt);
		printf("\n");
	}
}

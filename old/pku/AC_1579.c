/*
 * recursive plus memory search
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 21
long table[MAX][MAX][MAX];

long 
function_run_fun(int a, int b, int c)
{
	if(a<=0 || b<=0 || c<=0)
		return 1;
	if(a>20 || b>20 || c>20) 
		return (table[20][20][20] = function_run_fun(20, 20, 20));

	if(table[a][b][c] != 0) //memory search
		return table[a][b][c];

	else if(a<b && b<c)
		table[a][b][c] = function_run_fun(a, b, c-1) + function_run_fun(a, b-1, c-1) - function_run_fun(a, b-1, c);
	else
		table[a][b][c] = function_run_fun(a-1, b, c) + function_run_fun(a-1, b-1, c) + function_run_fun(a-1, b, c-1) - function_run_fun(a-1, b-1, c-1);
	return table[a][b][c];
}

int 
main(int argc, char **argv)
{
	int a, b, c;
	memset(table, 0, sizeof(long)*MAX*MAX*MAX);
	while(1) {
		scanf("%d %d %d", &a, &b, &c);
		if(a==-1 && b==-1 && c==-1)
			break;
		printf("w(%d, %d, %d) = %ld\n", a, b, c, function_run_fun(a, b, c));
	}
	return 0;
}

/* Time: 1532MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 10
char table[MAX_LEN][MAX_LEN];
int flag;

int
is_available(int x, int y, char ch)
{			
	int j, k, small_x, small_y;
	for(j=0; j<9; j++) /* row */
		if(table[x][j]==ch)
			return 0;
	for(k=0; k<9; k++) /* column */
		if(table[k][y]==ch)
			return 0;
	small_x = x/3;
	small_y = y/3;
	for(j=small_x*3; j<(small_x+1)*3; j++)
		for(k=small_y*3; k<(small_y+1)*3; k++)
			if(table[j][k]==ch)
				return 0;
	return 1;
}

void
dfs(int x, int y)
{
	int i, j, nx, ny;
	if(flag)
		return;
	if(x==9){
		if(!flag) {
			for(j=0; j<9; j++)
				printf("%s\n", table[j]);
			flag = 1;
		}
		return;
	}	
	if(y==8) {
		nx = x+1;
		ny = 0;
	} else {
		nx = x;
		ny = y+1;
	}
	if(table[x][y] == '0') {
		for(i=1; i<=9; i++) {
			if(is_available(x, y, i+'0')) {
				table[x][y] = i+'0';
				dfs(nx, ny);
				table[x][y] = '0';
			}
		}
	} else
		dfs(nx, ny);
}

int
main(int argc, char **argv)
{
	int i, tests;
	scanf("%d", &tests);
	while(tests--) {
		flag = 0;
		for(i=0; i<9; i++)
			scanf("%s", table[i]);
		dfs(0, 0);
	}
}

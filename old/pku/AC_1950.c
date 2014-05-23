#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_N 16
#define MAX_SOLVE 20
int total;
int n;
const int arr[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
const char op[] = {'+', '-', '.'};
char oparr[MAX_N];

void
output()
{
	int i;
	printf("1");
	for(i=0; i<n-1; i++) {
		printf(" %c ", oparr[i]);
		printf("%d", arr[i]);
	}
	printf("\n");
}

void
solve(int depth, int cur, int pre)
{
	if(depth+1 == n) {
		cur += pre;
		if(cur == 0) {
			++total;
			if(total <= MAX_SOLVE)
				output();
		}
		return;
	}
	oparr[depth] = op[0];
	solve(depth+1, cur+pre, arr[depth]);
	oparr[depth] = op[1];
	solve(depth+1, cur+pre, -arr[depth]);
	oparr[depth] = op[2];
	if(arr[depth]>=10)
		pre = pre*100 + pre/abs(pre)*arr[depth];
	else
		pre = pre*10 + pre/abs(pre)*arr[depth];
	solve(depth+1, cur, pre);
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &n)!=EOF) {
		total = 0;
		solve(0, 0, 1);
		printf("%d\n", total);
	}
}

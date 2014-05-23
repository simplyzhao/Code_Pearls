#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 42
#define MAX_SIZE 11
int size, n;
int used[MAX_LEN], pieces[MAX_SIZE];
int flag;

void
dfs(int depth)
{
	int i, j, col, min_used=MAX_LEN;
	if(depth == n) {
		flag = 1;
		return;
	}
	for(i=1; i<=size; i++)
		if(used[i] < min_used) {
			min_used = used[i];
			col = i;
		}
	for(i=10; i>=1; i--) {
		if(pieces[i]>0 && used[col]+i<=size && col+i-1<=size) {
			for(j=col; j<=col+i-1; j++)
				if(used[j]>min_used)
					break;
			if(j>col+i-1) {
				--pieces[i];
				for(j=col; j<=col+i-1; j++)
					used[j] += i;
				dfs(depth+1);
				for(j=col; j<=col+i-1; j++)
					used[j] -= i;
				++pieces[i];
			}
		}
	}
}

int
main(int argc, char **argv)
{
	int i, tmp, tests, sum;
	scanf("%d", &tests);
	while(tests--) {
		memset(used, 0, sizeof(used));
		memset(pieces, 0, sizeof(pieces));
		flag = 0;
		scanf("%d %d", &size, &n);
		sum = 0;
		for(i=0; i<n; i++) {
			scanf("%d", &tmp);
			++pieces[tmp];
			sum += (tmp*tmp);
		}
		if(sum == size*size)
			dfs(0);
		printf("%s\n", flag==1 ? "KHOOOOB!" : "HUTUTU!");
	}
}

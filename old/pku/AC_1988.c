#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 30005
int father[MAX_NUM], up[MAX_NUM], sum[MAX_NUM];

void
init()
{
	int i;
	for(i=1; i<MAX_NUM; i++) {
		father[i] = i;
		sum[i] = 1;
		up[i] = 0;
	}
}

int
find(int item)
{
	int tmp = father[item];
	if(father[item] != item) {
		father[item] = find(father[item]);
		up[item] += up[tmp];
	}
	return father[item];
}

void
uunion(int top, int down)
{
	int a = find(top);
	int b = find(down);
	if(a == b)
		return;
	father[b] = a;
	up[b] = sum[a];
	sum[a] += sum[b];
}

int
main(int argc, char **argv)
{
	int p, top, down, r, cube;
	char ch[2];
	scanf("%d", &p);
	init();
	while(p--) {
		scanf("%s", ch);
		if(ch[0] == 'M') {
			scanf("%d %d", &top, &down);
			uunion(top, down);
		} else {
			scanf("%d", &cube);
			r = find(cube);
			printf("%d\n", sum[r]-up[cube]-1);
		}
	}
}

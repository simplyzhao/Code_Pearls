#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 50001
int father[MAX_NUM];
int rank[MAX_NUM];
int total;

void
init(int n)
{
	int i;
	for(i=1; i<=n; i++)
		father[i] = i;
	memset(rank, 0, sizeof(rank));
	total = n;
}

int 
find(int item)
{
	if(father[item] != item)
		father[item] = find(father[item]);
	return father[item];
}

void
uunion(int item1, int item2)
{
	int a = find(item1);
	int b = find(item2);
	if(a == b)
		return;
	--total;
	if(rank[a] > rank[b])
		father[b] = a;
	else {
		father[a] = b;
		if(rank[a] == rank[b])
			++rank[b];
	}
}

int
main(int argc, char **argv)
{
	int n, m, i, j, k, cnt=0;
	while(scanf("%d %d", &n, &m)!=EOF) {
		if(n==0 && m==0)
			break;
		init(n);
		for(k=0; k<m; k++) {
			scanf("%d %d", &i, &j);
			uunion(i, j);
		}
		printf("Case %d: %d\n", ++cnt, total);
	}
}

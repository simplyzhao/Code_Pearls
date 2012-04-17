#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101
#define INF 0x7FFFFFFF
int adj[MAX_LEN][MAX_LEN];
int key[MAX_LEN], in[MAX_LEN];
int num, min;

void
prim()
{
	int i, j, k, cur;
	in[0] = 1;
	for(i=1; i<num; i++)
		if(adj[0][i])
			key[i] = adj[0][i];
	for(i=1; i<num; i++) {
		cur = INF;
		for(j=0; j<num; j++) 
			if(!in[j] && key[j]<cur) {
				cur = key[j];
				k = j;
			}
		min += cur;
		in[k] = 1;
		for(j=0; j<num; j++)
			if(adj[k][j])
				if(!in[j] && adj[k][j]<key[j])
					key[j] = adj[k][j];
	}
}

int
main(int argc, char **argv) 
{
	int i;
	while(scanf("%d", &num) != EOF) {
		min = 0;
		memset(adj, 0, sizeof(adj));
		memset(in, 0, sizeof(in));
		for(i=0; i<num; i++)
			key[i] = INF;
		for(i=0; i<num*num; i++)
			scanf("%d", &adj[i/num][i%num]);
		prim();
		printf("%d\n", min);
	}
}

/* MST problem */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 27
#define INF 0x7FFFFFFF
int num, min;
int adj[MAX_LEN][MAX_LEN];
int key[MAX_LEN], in[MAX_LEN];

void
init()
{
	int i, j, k, dis;
	char tmp[2], tmp1[2];
	memset(adj, 0, sizeof(adj));
	memset(in, 0, sizeof(in));
	min = 0;
	for(i=0; i<num; i++)
		key[i] = INF;
	for(i=0; i<num-1; i++) {
		scanf("%s %d", tmp, &k);
		for(j=0; j<k; j++) {
			scanf("%s %d", tmp1, &dis);
			adj[tmp[0]-'A'][tmp1[0]-'A'] = dis;
			adj[tmp1[0]-'A'][tmp[0]-'A'] = dis;
		}
	}
}

void
prim()
{
	int i, j, k, cur;
	/* start from vertex 'A' */
	in[0] = 1;
	for(i=1; i<num; i++)
		if(adj[0][i])
			key[i] = adj[0][i];
	for(i=1; i<num; i++) { /* num-1 vertex left */
		cur = INF;
		for(j=0; j<num; j++) {
			if(!in[j] && key[j]<cur) {
				cur = key[j];
				k = j;
			}
		}
		min += cur;
		in[k] = 1;
		for(j=0; j<num; j++) {
			if(adj[k][j]) {
				if(!in[j] && adj[k][j]<key[j])
					key[j] = adj[k][j];
			}
		}
	}
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &num)!=EOF && num) {
		init();
		prim();
		printf("%d\n", min);
	}
}

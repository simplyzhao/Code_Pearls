#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STR_LEN 207
#define MAX_N 26
int adj[MAX_N][MAX_N], in_dgr[MAX_N];
int visited[MAX_N];
int total, ch[MAX_N];
char ans[MAX_N];

int
init()
{
	int i, f, t, len;
	char str[STR_LEN];
	total = 0;
	memset(ch, 0, sizeof(ch));
	memset(in_dgr, 0, sizeof(in_dgr));
	memset(adj, 0, sizeof(adj));
	memset(visited, 0, sizeof(visited));
	memset(ans, 0, sizeof(ans));
	if(fgets(str, STR_LEN, stdin) == NULL)
		return 0;
	len = strlen(str);
	for(i=0; i<len; i+=2) {
		if(str[i]>='a' && str[i]<='z') {
			++total;
			++ch[str[i]-'a'];
		}
	}
	fgets(str, STR_LEN, stdin);
	len = strlen(str);
	for(i=0; i<len; i+=2) {
		if((i>>1)%2 == 0)
			f = str[i]-'a';
		else {
			t = str[i]-'a';
			adj[f][t] = 1;
			++in_dgr[t];
		}
	}
	return 1;
}

void
topo_sort(int depth)
{
	int i, j;
	if(depth == total) {
		printf("%s\n", ans);
		return;
	}
	for(i=0; i<MAX_N; i++) {
		if(ch[i] && !visited[i] && !in_dgr[i]) {
			visited[i] = 1;
			ans[depth] = 'a'+i;
			for(j=0; j<MAX_N; j++)
				if(adj[i][j])
					--in_dgr[j];
			topo_sort(depth+1);
			visited[i] = 0;
			for(j=0; j<MAX_N; j++)
				if(adj[i][j])
					++in_dgr[j];
		}
	}
}

int
main(int argc, char **argv)
{
	while(init()) {
		topo_sort(0);
		printf("\n");
	}
}

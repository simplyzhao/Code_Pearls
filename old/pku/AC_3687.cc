/* cpp: priority_queue */
#include<iostream>
#include<queue>
#include<vector>
#include<functional>
#include<cstdio>
#include<cstring>
using namespace std;

#define MAX_N 201
int n, m;
int adj[MAX_N][MAX_N];
int out_degree[MAX_N], topo[MAX_N], ans[MAX_N];

void
init()
{
	int i, pre, suc;
	memset(adj, 0, sizeof(adj));
	memset(out_degree, 0, sizeof(out_degree));
	scanf("%d %d", &n, &m);
	for(i=0; i<m; i++) {
		scanf("%d %d", &pre, &suc);
		if(!adj[pre][suc]) { /* avoid duplicates */
			adj[pre][suc] = 1;
			++out_degree[pre];
		}
	}
}

void
reverse_topo_sort()
{
	int i, tmp, count = 0;
	priority_queue<int, vector<int>, less<int> > Q;
	for(i=1; i<=n; i++)
		if(out_degree[i] == 0)
			Q.push(i);
	while(!Q.empty()) { /* BFS */
		tmp = Q.top();
		Q.pop();
		topo[++count] = tmp;
		for(i=1; i<=n; i++)
			if(adj[i][tmp]) {
				--out_degree[i];
				if(!out_degree[i])
					Q.push(i);
			}
	}
	if(count != n) { /* not DAG */
		printf("-1\n");
		return;
	}
	for(i=1; i<=n; i++)
		ans[topo[n-i+1]] = i;
	for(i=1; i<=n; i++)
		printf("%d ", ans[i]);
	printf("\n");
}

int
main(int argc, char **argv)
{
	int tests;
	scanf("%d", &tests);
	while(tests--) {
		init();
		reverse_topo_sort();
	}
}

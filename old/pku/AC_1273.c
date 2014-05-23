#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_M 201
#define INF 0x7FFFFFFF
#define Min(a,b) ((a)<(b) ? (a) : (b))
int n, m, source, sink;
int pre[MAX_M]; /* excellent for path recording */
int flow[MAX_M];
int residual[MAX_M][MAX_M]; /* only need this matrix */
int queue[MAX_M];

int
bfs() /* operation on the residual network */
{
	int i, head, tail, cur;
	head = -1;
	tail = 0;
	memset(pre, -1, sizeof(pre));
	for(i=1; i<=m; i++)
		flow[i] = INF;
	queue[tail] = source;
	pre[source] = 0;
	while(head < tail) {
		++head;
		cur = queue[head];
		if(cur == sink)
			return flow[sink];
		for(i=1; i<=m; i++) {
			if(pre[i]!=-1 || !residual[cur][i])
				continue;
			pre[i] = cur;
			flow[i] = Min(flow[cur], residual[cur][i]);
			++tail;
			queue[tail] = i;
		}
	}
	return -1;
}

int
edmonds_karp()
{
	int tmp, next, cur, rt = 0;
	while(1) {
		tmp = bfs();
		if(tmp == -1) /* there's no argment path */
			return rt;
		rt += tmp;
		cur = sink;
		while(cur != source) {
			next = cur;
			cur = pre[cur];
			residual[cur][next] -= tmp;
			residual[next][cur] += tmp;
		}
	}
}

int
main(int argc, char **argv)
{
	int i, f, t, c, ans;
	while(scanf("%d %d", &n, &m) != EOF) {
		memset(residual, 0, sizeof(residual));
		for(i=1; i<=n; i++) {
			scanf("%d %d %d", &f, &t, &c);
			residual[f][t] += c; /* Attention: multiple lines */
		}
		source = 1;
		sink = m;
		ans = edmonds_karp();
		printf("%d\n", ans);
	}
}

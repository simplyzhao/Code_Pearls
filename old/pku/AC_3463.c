#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 1001
#define INF 0x7FFFFFFF
int d[MAX_N][2], in[MAX_N][2], cnt[MAX_N][2];
int n, m, from, to;
struct Node {
	int target, cost;
	struct Node *next;
};
struct Node *nodes[MAX_N]; /* adj list: there may be different roads between city A and city B */

void
init()
{
	int i, f, t, c;
	struct Node *fresh;
	memset(nodes, 0, sizeof(nodes));
	scanf("%d %d", &n, &m);
	for(i=0; i<m; i++) {
		scanf("%d %d %d", &f, &t, &c);
		fresh = (struct Node *)malloc(sizeof(struct Node));
		fresh->target = t;
		fresh->cost = c;
		fresh->next = nodes[f];
		nodes[f] = fresh;
	}
	scanf("%d %d", &from, &to);
}

void
dijkstra()
{
	int i, j, k, p, min, v, cur;
	struct Node *tmp;
	memset(in, 0, sizeof(in));
	memset(cnt, 0, sizeof(cnt));
	/* d[i][0]: minimum path, d[i][1]: second minimum path */
	for(i=1; i<=n; i++)
		d[i][0] = d[i][1] = INF;
	d[from][0] = 0;
	cnt[from][0] = 1;
	for(i=1; i<=2*n; i++) { /* each vertex has two chance to relax */
		min = INF;
		p = -1;
		for(j=1; j<=n; j++) {
			if(!in[j][0] && d[j][0]<min) {
				min = d[j][0];
				p = j;
				k = 0;
			} else if(!in[j][1] && d[j][1]<min) {
				min = d[j][1];
				p = j;
				k = 1;
			}
		}
		if(p == -1)
			break;
		in[p][k] = 1;
		tmp = nodes[p];
		while(tmp != NULL) { /* Relax */
			v = tmp->target;
			cur = d[p][k] + tmp->cost;
			if(cur < d[v][0]) {
				d[v][1] = d[v][0];
				cnt[v][1] = cnt[v][0];
				d[v][0] = cur;
				cnt[v][0] = cnt[p][k];
			} else if(cur == d[v][0]) {
				cnt[v][0] += cnt[p][k];
			} else if(cur < d[v][1]) {
				d[v][1] = cur;
				cnt[v][1] = cnt[p][k];
			} else if(cur == d[v][1]) {
				cnt[v][1] += cnt[p][k];
			}
			tmp = tmp->next;
		}
	}
}

int
main(int argc, char **argv)
{
	int tests, rt;
	scanf("%d", &tests);
	while(tests--) {
		init();
		dijkstra();
		rt = cnt[to][0];
		if(d[to][0]+1 == d[to][1])
			rt += cnt[to][1];
		printf("%d\n", rt);
	}
}

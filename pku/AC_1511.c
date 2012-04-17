#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 1000005
#define INF 0x7FFFFFFF
struct Edge { /* build adj-list statically */
	int to;
	int cost;
	int next;
};
struct Edge edges[MAX_N], op_edges[MAX_N];
int assist[MAX_N], op_assist[MAX_N];
int mark[MAX_N], d[MAX_N];
int queue[MAX_N];
int P, Q;

void
init()
{
	int i, f, t, c;
	scanf("%d %d", &P, &Q);
	memset(assist, -1, sizeof(assist));
	memset(op_assist, -1, sizeof(op_assist));
	for(i=0; i<Q; i++) {
		scanf("%d %d %d", &f, &t, &c);
		edges[i].to = t;
		edges[i].cost = c;
		edges[i].next = assist[f];
		assist[f] = i;
		/* reverse graph */
		op_edges[i].to = f;
		op_edges[i].cost = c;
		op_edges[i].next = op_assist[t];
		op_assist[t] = i;
	}
}

long long
spfa(struct Edge *e, int *ass, int begin)
{
	int i, j, head, tail, cur;
	memset(mark, 0, sizeof(mark));
	for(i=1; i<=P; i++)
		d[i] = INF;
	head = -1;
	tail = 0;
	d[begin] = 0;
	mark[begin] = 1;
	queue[tail] = begin;
	while(head < tail) {
		++head;
		cur = queue[head];
		mark[cur] = 0;
		for(j=ass[cur]; j!=-1; j=e[j].next) {
			if(d[e[j].to] > d[cur]+e[j].cost) {
				d[e[j].to] = d[cur] + e[j].cost;
				if(!mark[e[j].to]) {
					++tail;
					queue[tail] = e[j].to;
					mark[e[j].to] = 1;
				}
			}
		}
	}
	long long rt = 0;
	for(i=1; i<=P; i++)
		rt += d[i];
	return rt;
}

int
main(int argc, char **argv)
{
	int tests;
	scanf("%d", &tests);
	while(tests--) {
		init();
		printf("%lld\n", spfa(edges, assist, 1)+spfa(op_edges, op_assist, 1));
	}
}

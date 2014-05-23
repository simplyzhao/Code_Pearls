#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 301
#define INF 0x7FFFFFFF
#define Min(a, b) ((a)<(b) ? (a) : (b))
struct Junction {
	int color; /* 0: blue, 1: purple */
	int left;
	int dur[2]; /* 0: blue, 1: purple */
}junctions[MAX_N];
int from, to;
int n, m;
int adj[MAX_N][MAX_N], d[MAX_N], in[MAX_N];

void
find_color(int index, int past, int *color, int *left) /* past: the time past from 0 */
{
	int i;
	if(past < junctions[index].left) {
		*color = junctions[index].color;
		*left = junctions[index].left - past;
		return;
	}
	past -= junctions[index].left;
	past = past%(junctions[index].dur[0] + junctions[index].dur[1]);
	if(junctions[index].color == 0) {
		if(past<junctions[index].dur[1]) {
			*color = 1;
			*left = junctions[index].dur[1] - past;
		} else {
			*color = 0;
			*left = junctions[index].dur[0] + junctions[index].dur[1] - past;
		}
	}
	else {
		if(past<junctions[index].dur[0]) {
			*color = 0;
			*left = junctions[index].dur[0] - past;
		} else {
			*color = 1;
			*left = junctions[index].dur[0] + junctions[index].dur[1] - past;
		}
	}
}

void
update(int index, int bt) /* bt: the beginning time for current update */
{
	int i, tm, color_a, color_b, left_a, left_b;
	for(i=1; i<=n; i++) {
		if(!in[i] && adj[index][i] && d[i]>bt+adj[index][i]) {
			find_color(index, bt, &color_a, &left_a);
			find_color(i, bt, &color_b, &left_b);
			if(color_a == color_b)
				tm = 0;
			else {
				if(left_a != left_b)
					tm = Min(left_a, left_b);
				else {
					if(color_a == 0) {
						if(junctions[index].dur[1] != junctions[i].dur[0])
							tm = left_a + Min(junctions[index].dur[1], junctions[i].dur[0]);
						else if(junctions[index].dur[0] != junctions[i].dur[1])
							tm = left_a + junctions[index].dur[1] + Min(junctions[index].dur[0], junctions[i].dur[1]);
						else
							tm = INF;
					}
					else {
						if(junctions[index].dur[0] != junctions[i].dur[1])
							tm = left_a + Min(junctions[index].dur[0], junctions[i].dur[1]);
						else if(junctions[index].dur[1] != junctions[i].dur[0])
							tm = left_a + junctions[index].dur[0] + Min(junctions[index].dur[1], junctions[i].dur[0]);
						else
							tm = INF;
					}
				}
			}
			if(tm!=INF && d[i]>d[index]+adj[index][i]+tm)
				d[i] = d[index]+adj[index][i]+tm;
		}
	}
}

void
dijkstra(int source)
{
	int i, j, k, cur;
	memset(in, 0, sizeof(in));
	for(i=1; i<=n; i++)
		d[i] = INF;
	in[source] = 1;
	d[source] = 0;
	update(source, 0);
	for(i=2; i<=n; i++) {
		cur = INF;
		for(j=1; j<=n; j++)
			if(!in[j] && d[j]<=cur) {
				k = j;
				cur = d[j];
			}
		in[k] = 1;
		if(k == to)
			break;
		if(d[k] != INF)
			update(k, d[k]);
	}
}

void
input_init()
{
	int i, f, t, c;
	char tmp[2];
	scanf("%d %d", &n, &m);
	for(i=1; i<=n; i++) {
		scanf("%s %d %d %d", tmp, &junctions[i].left, &(junctions[i].dur[0]), &(junctions[i].dur[1]));
		junctions[i].color = (tmp[0]=='B' ? 0 : 1);
	}
	memset(adj, 0, sizeof(adj));
	for(i=0; i<m; i++) {
		scanf("%d %d %d", &f, &t, &c);
		adj[f][t] = c;
		adj[t][f] = c;
	}
}

int
main(int argc, char **argv)
{
	while(scanf("%d %d", &from, &to) != EOF) {
		input_init();
		dijkstra(from);
		printf("%d\n", d[to]==INF ? 0 : d[to]);
	}
}

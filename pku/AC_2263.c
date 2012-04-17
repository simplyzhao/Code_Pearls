#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 201
#define MAX_LEN 31
#define INF 0x7FFFFFFF
#define HASH_LEN 19999
#define Min(a, b) ((a)<(b) ? (a) : (b))
#define Max(a, b) ((a)<(b) ? (b) : (a))
int n, r, hash_val;
int from, to, adj[MAX_N][MAX_N];
int d[MAX_N], in[MAX_N];
struct City{
	char name[MAX_LEN];
	int num;
} cities[MAX_N];
struct Node {
	int index;
	struct Node *next;
};
struct Node *hash[HASH_LEN] = {NULL};

int ELFHash(char *str)
{
	unsigned long t, hash = 0;
	while(*str) {
		hash = (hash<<4) + (*str++);
		if((t = hash&0xF0000000L))
			hash ^= t>>24;
		hash &= ~t;
	}
	return (hash & 0x7FFFFFFF)%HASH_LEN;
}

void
insert(int index)
{
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	node->index = index;
	node->next = hash[hash_val];
	hash[hash_val] = node;
}

int
search(char *str)
{
	struct Node *node = hash[hash_val];
	while(node != NULL) {
		if(strcmp(str, cities[node->index].name) == 0)
			return cities[node->index].num;
		node = node->next;
	}
	return -1;
}

void
init()
{
	int i, j, mark, f, t, c;
	char str[MAX_LEN];
	memset(hash, 0, sizeof(hash));
	memset(adj, 0, sizeof(adj));
	for(j=0, mark=1, i=0; i<r; i++) {
		scanf("%s", cities[j].name);
		hash_val = ELFHash(cities[j].name);
		if((f=search(cities[j].name)) == -1) {
			insert(j);
			cities[j].num = mark++;
			f = cities[j].num;
			j++;
		}
		scanf("%s", cities[j].name);
		hash_val = ELFHash(cities[j].name);
		if((t=search(cities[j].name)) == -1) {
			insert(j);
			cities[j].num = mark++;
			t = cities[j].num;
			j++;
		}
		scanf("%d", &c);
		if(adj[f][t] < c)
			adj[f][t] = adj[t][f] = c;
	}
	scanf("%s", str);
	hash_val = ELFHash(str);
	from = search(str);
	scanf("%s", str);
	hash_val = ELFHash(str);
	to = search(str);
}

void
solve()
{
	int i, j, k, tmp;
	memset(in, 0, sizeof(in));
	for(i=1; i<=n; i++)
		d[i] = 0;
	d[from] = INF;
	in[from] = 1;
	for(i=1; i<=n; i++) {
		if(adj[from][i])
			d[i] = adj[from][i];
	}

	k = n-1;
	while(k > 0) {
		for(i=1; i<=n; i++) {
			if(!in[i] && d[i]!=0) {
				for(j=1; j<=n; j++) {
					if(adj[i][j]) {
						tmp = Min(d[i], adj[i][j]);
						d[j] = Max(d[j], tmp);
					}
				}
				in[i] = 1;
				--k;
			}
		}
	}
}

int
main(int argc, char **argv)
{
	int tests = 0;
	while(scanf("%d %d", &n, &r) != EOF) {
		if(n==0 && r==0)
			break;
		init();
		solve();
		printf("Scenario #%d\n%d tons\n\n", ++tests, d[to]);
	}
}

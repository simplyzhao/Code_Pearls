#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 501
#define Abs(a) ((a)>=0 ? (a) : (a)*(-1))
int M;
int graph[MAX_LEN][MAX_LEN];
int state[MAX_LEN], fwd[MAX_LEN], bwd[MAX_LEN];
struct Taxi {
	int hour, minu;
	int sx, sy, dx, dy;
}rides[MAX_LEN];

int
reachable(struct Taxi *fst, struct Taxi *scd)
{
	int h, m;
	h = fst->hour;
	m = fst->minu + Abs(fst->dx-fst->sx) + Abs(fst->dy-fst->sy) + Abs(scd->sx-fst->dx) + Abs(scd->sy-fst->dy);
	h = (h+m/60);
	m = m%60;
	if(h >= 24)
		return 0;
	if(h == scd->hour)
		return (m<scd->minu);
	return (h<scd->hour);
}

void
build_graph()
{
	int i, j;
	memset(graph, 0, sizeof(graph));
	for(i=0; i<M; i++)
		for(j=i+1; j<M; j++)
			if(reachable(rides+i, rides+j))
				graph[i][j] = 1;
}

int
find_path(int u)
{
	int i;
	for(i=0; i<M; i++) {
		if(graph[u][i] && !state[i]) {
			state[i] = 1;
			if(bwd[i]==-1 || find_path(bwd[i])) {
				bwd[i] = u;
				fwd[u] = i;
				return 1;
			}
		}
	}
	return 0;
}

int 
MaxMatch()
{
	int i, ans = 0;
	memset(fwd, -1, sizeof(fwd));
	memset(bwd, -1, sizeof(bwd));
	for(i=0; i<M; i++) {
		if(fwd[i] == -1) {
			memset(state, 0, sizeof(state));
			if(find_path(i))
				++ans;
		}
	}
	return ans;
}

int
main(int argc, char **argv)
{
	int i, tests;
	scanf("%d", &tests);
	while(tests--) {
		scanf("%d", &M);
		for(i=0; i<M; i++) 
			scanf("%d:%d %d %d %d %d", &rides[i].hour, &rides[i].minu, &rides[i].sx, &rides[i].sy, &rides[i].dx, &rides[i].dy);
		build_graph();
		printf("%d\n", M-MaxMatch());
	}
}

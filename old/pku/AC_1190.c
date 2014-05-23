/*
 * N = R[1]^2*H[1] + R[2]^2*H[2] + ... + R[M]^2*H[M]
 * S = R[1]^2 + 2R[1]*H[1] + 2R[2]*H[2] + ... + 2R[M]H[M]
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_LEVEL 21
#define INF 0x7FFFFFFF
/* from top level to the i[th] level, the minimum total volumn and area */
int min_volumn[MAX_LEVEL], min_area[MAX_LEVEL];
int n, m;
int rt;

void
init()
{
	int i;
	rt = INF;
	min_volumn[0] = min_area[0] = 0;
	for(i=1; i<MAX_LEVEL; i++) {
		min_volumn[i] = min_volumn[i-1] + i*i*i;
		min_area[i] = min_area[i-1] + 2*i*i;
	}
}

/* from bottom(m[th] level) to the top */
void
dfs(int level, int last_r, int last_h, int cur_volumn, int cur_area)
{
	int r, h, tmp, v, a;
	if(cur_volumn+min_volumn[level]>n || cur_area+min_area[level]>=rt)
		return;
	/* ADD this pruning according the volumn&area formula */
	if(2*(n-cur_volumn)/last_r+cur_area >= rt)
		return;
	if(level==0) {
		if(cur_volumn == n)
			rt = cur_area<rt ? cur_area : rt;
		return;
	}
	/* the minimal r in [level] would be level */
	for(r=last_r-1; r>=level; r--) {
		tmp = (int)((n-cur_volumn-min_volumn[level-1])/(double)(r*r));
		tmp = tmp>(last_h-1) ? (last_h-1) : tmp;
		for(h=tmp; h>=level; h--) {
			v = r*r*h;
			a = 2*r*h;
			if(level == m)
				a += (r*r);
			dfs(level-1, r, h, cur_volumn+v, cur_area+a);
		}
	}
}

int
main(int argc, char **argv)
{
	int max_m_r, max_m_h;
	while(scanf("%d %d", &n, &m) != EOF) {
		init();
		max_m_r = (int)(sqrt((n-min_volumn[m-1])/(double)m)) + 1;
		max_m_h = (int)((n-min_volumn[m-1])/(double)(m*m)) + 1;
		dfs(m, max_m_r, max_m_h, 0, 0);
		if(rt == INF)
			printf("0\n");
		else
			printf("%d\n", rt);
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_LEN 101
int map[MAX_LEN][MAX_LEN];
int result[MAX_LEN]; /* previous matching */
int state[MAX_LEN];
int n, m, s, v;
struct Coordinate {
	float x, y;
}gophers[MAX_LEN], holes[MAX_LEN];

int
findpath(int u)
{
	int i;
	for(i=0; i<m; i++) {
		if(map[u][i] && state[i]==-1) {
			state[i] = 1;
			if(result[i]==-1 || findpath(result[i])) {
				result[i] = u; /* 取反 */
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
	for(i=0; i<n; i++) {
		memset(state, -1, sizeof(state));
		if(findpath(i))
			++ans;
	}
	return ans;
}

int
main(int argc, char **argv)
{
	int i, j;
	while(scanf("%d %d %d %d", &n, &m, &s, &v) != EOF) {
		for(i=0; i<n; i++)
			scanf("%f %f", &gophers[i].x, &gophers[i].y);
		for(j=0; j<m; j++)
			scanf("%f %f", &holes[j].x, &holes[j].y);

		memset(map, 0, sizeof(map));
		memset(result, -1, sizeof(result));
		for(i=0; i<n; i++) 
			for(j=0; j<m; j++) {
				if(sqrt((holes[j].x-gophers[i].x)*(holes[j].x-gophers[i].x) + (holes[j].y-gophers[i].y)*(holes[j].y-gophers[i].y)) <= v*s) /*reachable*/
					map[i][j] = 1;
				else
					map[i][j] = 0;
			}

		printf("%d\n", n-MaxMatch());
	}
}

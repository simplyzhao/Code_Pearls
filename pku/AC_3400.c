#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 11
struct Stone {
	int weight;
	int cost;
}stones[MAX_LEN];
int N, D;
int total_cost, max_cost, hash[MAX_LEN];

void
dfs(char bunker, int weight_a, int cost_a, int weight_b, int cost_b)
{
	int i, w, c, mark = 0;
	if(total_cost-cost_a<=max_cost)
		return;
	for(i=0; i<N; i++) {
		if(!hash[i]) {
			mark = 1;
			hash[i] = 1;
			switch(bunker) {
				case 'A':
					w = weight_a+stones[i].weight;
					c = cost_a+stones[i].cost;
					if(w-weight_b <= D)
						dfs('A', w, c, weight_b, cost_b);
					else
						dfs('B', w, c, weight_b, cost_b);
					break;
				case 'B':
					w = weight_b+stones[i].weight;
					c = cost_b+stones[i].cost;
					if(w-weight_a <= D)
						dfs('B', weight_a, cost_a, w, c);
					else
						dfs('A', weight_a, cost_a, w, c);
					break;
			}
			hash[i] = 0;
		}
	}
	if(!mark) 
		max_cost = max_cost<cost_b ? cost_b : max_cost;
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %d", &N, &D) != EOF) {
		total_cost = 0;
		for(i=0; i<N; i++) {
			scanf("%d %d", &stones[i].weight, &stones[i].cost);
			total_cost += stones[i].cost;
		}
		max_cost = 0;
		memset(hash, 0, sizeof(hash));
		dfs('A', 0, 0, 0, 0);
		printf("%d\n", max_cost);
	}
}

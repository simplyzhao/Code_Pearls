/* union-find set */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 30001
int parent[MAX_LEN];

void
init(int size)
{
	int i;
	for(i=0; i<size; i++)
		parent[i] = -1;
}

int
find(int item)
{
	int tmp, root = item;
	while(parent[root] >= 0)
		root = parent[root];
	while(item != root) {
		tmp = parent[item];
		parent[item] = root;
		item = tmp;
	}
	return root;
}

void
uunion(int item1, int item2)
{
	int root1 = find(item1);
	int root2 = find(item2);
	if(root1 != root2) {
		if(parent[root1] < parent[root2]) { /* tree with 'root1' has more nodes */
			parent[root1] += parent[root2];
			parent[root2] = root1;
		} else {
			parent[root2] += parent[root1];
			parent[root1] = root2;
		}
	}
}

int
main(int argc, char **argv)
{
	int n, m, gp, i, j, r, stu;
	while(scanf("%d %d", &n, &m)!=EOF) {
		if(n==0 && m==0)
			break;
		init(n);
		for(i=0; i<m; i++) {
			scanf("%d", &gp);
			for(j=0; j<gp; j++) {
				scanf("%d", &stu);
				if(j==0)
					r = stu;
				else
					uunion(r, stu);
			}
		}
		printf("%d\n", -parent[find(0)]);
	}
}

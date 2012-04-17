#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STR_LEN 18
#define MAX_NUM 1001
struct Desc {
	char key[STR_LEN];
	int value;
}dic[MAX_NUM];
int m, n;

int
cmp(const void *arg1, const void *arg2)
{
	return strcmp(((struct Desc *)arg1)->key, ((struct Desc *)arg2)->key);
}

void
init()
{
	int i;
	for(i=0; i<m; i++)
		scanf("%s %d", dic[i].key, &dic[i].value);
	qsort(dic, m, sizeof(struct Desc), cmp);
}

void
solve()
{
	int total;
	struct Desc p, *t;
	while(n--) {
		total = 0;
		while(1) {
			scanf("%s", p.key);
			if(p.key[0] == '.') {
				printf("%d\n", total);
				break;
			}
			if((t=bsearch(&p, dic, m, sizeof(struct Desc), cmp)) == NULL)
				continue;
			total += (((struct Desc *)t)->value);
		}
	}
}

int
main(int argc, char **argv)
{
	while(scanf("%d %d", &m, &n) != EOF) {
		init();
		solve();
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define QUEUE_LEN 25000
#define MAX_VOL 1001
const char ops[][12] = {
	"fill A",
	"fill B",
	"empty A",
	"empty B",
	"pour A B",
	"pour B A" };
int vola, volb, target;
int head, tail;
int visited[MAX_VOL][MAX_VOL];
struct EACH {
	int a, b;
	int opnum;
	int opidx;
	struct EACH *pre;
} queue[QUEUE_LEN];

#define ADD(na, nb, num, idx) ++tail; \
	queue[tail].a = na; \
    queue[tail].b = nb; \
	queue[tail].opnum = num+1; \
	queue[tail].opidx = idx; \
    queue[tail].pre = queue+head; \
    visited[na][nb] = 1;

void
output(struct EACH *item)
{
	if(item == NULL)
		return;
	output(item->pre);
	if(item->opidx >= 0)
		printf("%s\n", ops[item->opidx]);
}

void
bfs()
{
	int cur_a, cur_b, ta, tb, cur_opnum;
	queue[tail].a = 0;
	queue[tail].b = 0;
	queue[tail].opnum = 0;
	queue[tail].opidx = -1;
	queue[tail].pre = NULL;
	visited[0][0] = 1;
	while(head < tail) {
		++head;
		cur_a = queue[head].a;
		cur_b = queue[head].b;
		cur_opnum = queue[head].opnum;
		if(cur_b==target) {
			output(queue+head);
			printf("success\n");
			return;
		}
		if(!visited[vola][cur_b]) { /* FILL(1) */
			ADD(vola, cur_b, cur_opnum, 0);
		}
		if(!visited[cur_a][volb]) { /* FILL(2) */
			ADD(cur_a, volb, cur_opnum, 1);
		}
		if(!visited[0][cur_b]) { /* DROP(1) */
			ADD(0, cur_b, cur_opnum, 2);
		}
		if(!visited[cur_a][0]) { /* DROP(2) */
			ADD(cur_a, 0, cur_opnum, 3);
		}
		/* POUR(1,2) */
		if(cur_a+cur_b > volb) {
			ta = cur_a+cur_b-volb;
			tb = volb;
			if(!visited[ta][tb]) {
				ADD(ta, tb, cur_opnum, 4);
			}
		} else {
			ta = 0;
			tb = cur_a + cur_b;
			if(!visited[ta][tb]) {
				ADD(ta, tb, cur_opnum, 4);
			}
		}
		/* POUR(2,1) */
		if(cur_a+cur_b > vola) {
			ta = vola;
			tb = cur_a+cur_b-vola;
			if(!visited[ta][tb]) {
				ADD(ta, tb, cur_opnum, 5);
			}
		} else {
			ta = cur_a + cur_b;
			tb = 0;
			if(!visited[ta][tb]) {
				ADD(ta, tb, cur_opnum, 5);
			}
		}
	}
	printf("impossible\n");
}

int
main(int argc, char **argv)
{
	while(scanf("%d %d %d", &vola, &volb, &target) != EOF) {
		head = -1;
		tail = 0;
		memset(queue, 0, sizeof(queue));
		memset(visited, 0, sizeof(visited));
		bfs();
	}
	return 0;
}

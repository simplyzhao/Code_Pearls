/* A-star */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STR_LEN 9
#define HASH_LEN 362880 /* 9! */
const int facs[] = {1, 2, 6, 24, 120, 720, 5040, 40320};
const char letters[] = "udlr";
const int pos[] = {-3, 3, -1, 1}; /* up, down, left, right */
const int movable[][4] = {0,1,0,1, 0,1,1,1, 0,1,1,0, 1,1,0,1, 1,1,1,1, 1,1,1,0, 1,0,0,1, 1,0,1,1, 1,0,1,0};
const int points[][2] = {{0,0}, {1,0}, {2,0}, {0,-1}, {1,-1}, {2,-1}, {0,-2}, {1,-2}, {2,-2}};
int distance[STR_LEN][STR_LEN];
struct EACH {
	char str[STR_LEN+1];
	int pos, value;
} queue[HASH_LEN];
int pre[HASH_LEN], dir[HASH_LEN], g[HASH_LEN], h[HASH_LEN], idx[HASH_LEN];
int mark[HASH_LEN]; /* 0: unvisited / 1: open-list / 2: closed-list */
int target; /* target hash value: "123456780" */

/* ------begin: priority queue ------*/
int count;
#define LEFT_CLD(i) ((i<<1)+1)
#define RIGHT_CLD(i) ((i+1)<<1)
#define PARENT(i) ((i-1)>>1)

int
compare_item(struct EACH *arg1, struct EACH *arg2)
{
	return ((g[arg1->value] + h[arg1->value]) - (g[arg2->value] + h[arg2->value]));
}

void
swap(i, j)
{
	struct EACH tmp = queue[i];
	queue[i] = queue[j];
	queue[j] = tmp;
	idx[queue[i].value] = j;
	idx[queue[j].value] = i;
}

void
min_heapify(int heapsize, int i)
{
	int min = i;
	int left = LEFT_CLD(i);
	int right = RIGHT_CLD(i);
	if(left<heapsize && compare_item(queue+min, queue+left)>0)
		min = left;
	if(right<heapsize && compare_item(queue+min, queue+right)>0)
		min = right;
	if(min != i) {
		swap(i, min);
		min_heapify(heapsize, min);
	}
}

struct EACH
pop()
{
	struct EACH rt = queue[0];
	swap(0, count-1);
	--count;
	min_heapify(count, 0);
	return rt;
}

void
up_heapify(int from)
{
	int cld, pt;
	cld = from;
	pt = PARENT(cld);
	while(cld>0 && compare_item(queue+cld, queue+pt)<0) {
		swap(cld, pt);
		cld = pt;
		pt = PARENT(cld);
	}
}

void
push(struct EACH item)
{
	int cld, pt;
	++count;
	queue[count-1] = item;
	up_heapify(count-1);
}
/* -------end: priority queue -------*/

/* permutation -> number */
int 
hash_func(char *str)
{
	int i, j, cnt, result = 0;
	for(i=1; i<STR_LEN; i++) {
		cnt = 0;
		for(j=0; j<i; j++)
			if(str[j] > str[i])
				++cnt;
		result += (cnt*facs[i-1]);
	}
	return result;
}

int
dist(int i, int j)
{
	int px, py;
	px = points[i][0] - points[j][0];
	py = points[i][1] - points[j][1];
	px = px>=0 ? px : -px;
	py = py>=0 ? py : -py;
	return px+py;
}

/* estimate function: manhattan distance */
int
estimate(char *str)
{
	int i, rt = 0;
	for(i=0; i<STR_LEN; i++)
		if(str[i] != '0')
			rt += distance[i][str[i]-'0'-1];
	return rt;
}

void
output(int hash_value)
{
	if(pre[hash_value] == -1)
		return;
	output(pre[hash_value]);
	printf("%c", letters[dir[hash_value]]);
}

void
Astar(char *start_str, int start_pos)
{
	int i, th, hvalue, curp, nxtp;
	char nxt[STR_LEN+1];
	struct EACH cur, tmp;
	strcpy(queue[0].str, start_str);
	queue[0].pos = start_pos;
	queue[0].value = hash_func(start_str);
	count = 1;
	mark[queue[0].value] = 1; /* open list */
	g[queue[0].value] = 0;
	h[queue[0].value] = estimate(start_str);
	pre[queue[0].value] = -1;
	dir[queue[0].value] = -1;
	idx[queue[0].value] = 0;
	while(count != 0) {
		cur = pop();
		if(cur.value == target) {
			output(target);
			printf("\n");
			return;
		}
		mark[cur.value] = 2; /* add to closed-list */
		curp = cur.pos;
		for(i=0; i<4; i++) {
			if(movable[curp][i]) {
				nxtp = curp + pos[i];
				strcpy(nxt, cur.str);
				nxt[curp] = nxt[nxtp];
				nxt[nxtp] = '0';
				hvalue = hash_func(nxt);
				if(mark[hvalue]==1 && g[hvalue]>(g[cur.value]+1)) { /* update */
					g[hvalue] = g[cur.value]+1;
					pre[hvalue] = cur.value;
					dir[hvalue] = i;
					up_heapify(idx[hvalue]);
				} else if(mark[hvalue]==0) { /* add to open-list */
					strcpy(tmp.str, nxt);
					tmp.pos = nxtp;
					tmp.value = hvalue;
					mark[hvalue] = 1;
					g[hvalue] = g[cur.value]+1;
					h[hvalue] = estimate(nxt);
					pre[hvalue] = cur.value;
					dir[hvalue] = i;
					idx[hvalue] = count;
					push(tmp);
				}
			}
		}
	}
	printf("unsolvable\n");
}

int
main(int argc, char **argv)
{
	int i, j, len, sp, cnt=0;
	char input[STR_LEN*5], num[STR_LEN+1];
	fgets(input, STR_LEN*5-1, stdin);
	len = strlen(input);
	for(i=0; i<len; i++) {
		if(input[i]>='0' && input[i]<='8')
			num[cnt++] = input[i];
		else if(input[i]=='x') {
			num[cnt++] = '0';
			sp = cnt-1;
		}
	}
	num[STR_LEN] = '\0';
	for(i=0; i<STR_LEN; i++)
		for(j=0; j<STR_LEN; j++)
			distance[i][j] = dist(i, j);
	memset(pre, -1, sizeof(pre));
	memset(dir, -1, sizeof(dir));
	memset(idx, -1, sizeof(idx));
	memset(mark, 0, sizeof(mark));
	memset(g, 0, sizeof(g));
	memset(h, 0, sizeof(h));
	target = hash_func("123456780");
	Astar(num, sp);
	return 0;
}

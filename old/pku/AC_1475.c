#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 21
/* north, south, east, west */
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const char dir_box[] = "NSEW";
const char dir_psn[] = "nsew";
int r, c;
int px, py, bx, by, btx, bty;
char map[MAX_LEN][MAX_LEN];
struct EACH {
	int x, y;
	int id;
	int pre;
	int dir;
};
struct EACH cur_each, tmp_each, cur_psn, tmp_psn, box_queue[MAX_LEN*MAX_LEN], psn_queue[MAX_LEN*MAX_LEN];
struct {
	int x, y;
}persons[MAX_LEN*MAX_LEN];
int visited_box[MAX_LEN][MAX_LEN];
int visited_psn[MAX_LEN][MAX_LEN];
int cnt[MAX_LEN*MAX_LEN];
char seq[MAX_LEN*MAX_LEN][MAX_LEN*MAX_LEN];

int
is_valid_box(struct EACH item, int dir)
{
	int tmpx, tmpy;
	if(item.x<0 || item.x>=r || item.y<0 || item.y>=c || map[item.x][item.y]=='#')
		return 0;
	/* see if there exists a position for person to push */
	tmpx = item.x-2*dx[dir];
	tmpy = item.y-2*dy[dir];
	if(tmpx<0 || tmpx>=r || tmpy<0 || tmpy>=c || map[tmpx][tmpy]=='#')
		return 0;
	return 1;
}

int
is_valid_psn(int psnx, int psny, int boxx, int boxy)
{
	if(psnx<0 || psnx>=r || psny<0 || psny>=c || map[psnx][psny]=='#')
		return 0;
	/* path of person can't cover the box */
	if(psnx==boxx && psny==boxy)
		return 0;
	return 1;
}

int
psn_bfs(int startx, int starty, int endx, int endy, int dir, int index)
{
	int i, head, tail;
	struct EACH tmp;
	memset(visited_psn, 0, sizeof(visited_psn));
	head = -1;
	tail = 0;
	psn_queue[tail].x = startx;
	psn_queue[tail].y = starty;
	psn_queue[tail].pre = -1;
	visited_psn[startx][starty] = 1;
	while(head < tail) {
		++head;
		cur_psn = psn_queue[head];
		if(cur_psn.x==endx && cur_psn.y==endy) {
			/* record */
			/* here 'index' should plus 1, according to box_bfs */
			persons[index+1].x = cur_psn.x + dx[dir];
			persons[index+1].y = cur_psn.y + dy[dir];
			cnt[index+1] = 0;
			tmp = cur_psn;
			while(tmp.pre != -1) {
				seq[index+1][cnt[index+1]++] = dir_psn[tmp.dir];
				tmp = psn_queue[tmp.pre];
			}
			return 1;
		}
		for(i=0; i<4; i++) {
			tmp_psn.x = cur_psn.x + dx[i];
			tmp_psn.y = cur_psn.y + dy[i];
			if(is_valid_psn(tmp_psn.x, tmp_psn.y, endx+dx[dir], endy+dy[dir]) && !visited_psn[tmp_psn.x][tmp_psn.y]) {
				++tail;
				tmp_psn.pre = head;
				tmp_psn.dir = i;
				psn_queue[tail] = tmp_psn;
				visited_psn[tmp_psn.x][tmp_psn.y] = 1;
			}
		}
	}
	return 0;
}

void
output(struct EACH *end)
{
	int i, index;
	if(end->pre == -1)
		return;
	output(box_queue+(end->pre));
	index = end->id;
	for(i=cnt[index]-1; i>=0; i--)
		printf("%c", seq[index][i]);
	printf("%c", dir_box[end->dir]);
}

void
box_bfs()
{
	int i, psn_rt, head, tail;
	head = -1;
	tail = 0;
	memset(visited_box, 0, sizeof(visited_box));
	box_queue[tail].x = bx;
	box_queue[tail].y = by;
	box_queue[tail].pre = -1;
	box_queue[tail].id = tail;
	visited_box[bx][by] = 1;
	persons[tail].x = px;
	persons[tail].y = py;
	while(head < tail) {
		++head;
		cur_each = box_queue[head];
		if(cur_each.x==btx && cur_each.y==bty) {
			/* output */
			output(box_queue+head);
			return;
		}
		for(i=0; i<4; i++) {
			tmp_each.x = cur_each.x + dx[i];
			tmp_each.y = cur_each.y + dy[i];
			if(is_valid_box(tmp_each, i) && !visited_box[tmp_each.x][tmp_each.y]) {
				/* bfs for person */
				psn_rt = psn_bfs(persons[head].x, persons[head].y, tmp_each.x-2*dx[i], tmp_each.y-2*dy[i], i, tail);
				if(psn_rt) {
					++tail;
					tmp_each.dir = i;
					tmp_each.pre = head;
					tmp_each.id = tail;
					box_queue[tail] = tmp_each;
					visited_box[tmp_each.x][tmp_each.y] = 1;
				}
			}
		}
	}
	printf("Impossible.");
}

int
main(int argc, char **argv)
{
	int i, j, tests = 0;
	while(scanf("%d %d", &r, &c) != EOF) {
		if(r==0 && c==0)
			break;
		for(i=0; i<r; i++) {
			scanf("%s", map[i]);
			for(j=0; j<c; j++) {
				if(map[i][j] == 'S') {
					px = i;
					py = j;
				} else if(map[i][j] == 'B') {
					bx = i;
					by = j;
				} else if(map[i][j] == 'T') {
					btx = i;
					bty = j;
				}
			}
		}
		printf("Maze #%d\n", ++tests);
		/* bfs */
		box_bfs();
		printf("\n\n");
	}
}

/* bidirectional BFS */
/* Memory: 2704K Time: 47MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BOARD 8
#define MOVE_MAX 8
#define PRIME 10007
#define HASH_MAX PRIME
#define is_set(i, j, state) (state & (((unsigned long long)1)<<((i)*BOARD+(j))))
#define set_bit(i, j, state) (state |= (((unsigned long long)1)<<((i)*BOARD+(j))))
#define clear_bit(i, j, state) (state &= (~(((unsigned long long)1)<<((i)*BOARD+(j)))))
#define is_valid(i, j) (i>=0 && i<BOARD && j>=0 && j<BOARD)
struct Node {
	/* 8x8 chessboard can be represented by 64 bits */
	unsigned long long state;
	short move;
}queue[63537], second_queue[63537];
unsigned long long begin, end;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
int head, tail, second_head, second_tail;
struct Hash {
	unsigned long long *pstate;
	struct Hash *next;
}hash_table[HASH_MAX], second_hash_table[HASH_MAX];

int
check_hash(struct Hash *hash, unsigned long long value)
{
	int index = value % PRIME;
	struct Hash *p = hash[index].next;
	while(p != NULL) {
		if(*(p->pstate) == value) 
			return 1;
		p = p->next;
	}
	return 0;
}

void
insert_hash(struct Hash *hash, unsigned long long *pstate, int index)
{
	struct Hash *node = malloc(sizeof(struct Hash));
	node->pstate = pstate;
	node->next = hash[index].next;
	hash[index].next = node;
}

int
bfs()
{
	int i, j, x, y, next_x, next_y, cnt, cur_move, second_cur_move;
	cur_move = second_cur_move = 0;
	unsigned long long cur_state, next_state;
	queue[tail].state = begin;
	queue[tail].move = 0;
    insert_hash(hash_table, &(queue[tail].state), (queue[tail].state)%PRIME);
	second_queue[second_tail].state = end;
	second_queue[second_tail].move = 0;
    insert_hash(second_hash_table, &(second_queue[second_tail].state), (second_queue[second_tail].state)%PRIME);
	while(head<tail && second_head<second_tail) {
		++head;
		cnt = 0;
		cur_state = queue[head].state;
		cur_move = queue[head].move;
		for(i=0; i<64 && cnt<4; i++) {
			if(cur_state & (((unsigned long long)1)<<i)) {
				++cnt;
				x = i/BOARD;
				y = i%BOARD; 
				for(j=0; j<4; j++) { /* left, right, up, down */
					next_x = x + dx[j];
					next_y = y + dy[j];
					if(!is_valid(next_x, next_y))
						continue;
					if(is_set(next_x, next_y, cur_state)) {
						next_x += dx[j];
						next_y += dy[j];
						if(!is_valid(next_x, next_y))
							continue;
					}
					/* make sure the next state never showed before */
					/* hash: one of the most powerful tools */
					next_state = cur_state;
					clear_bit(x, y, next_state);
					set_bit(next_x, next_y, next_state);
					if(!check_hash(hash_table, next_state) && cur_move<MOVE_MAX/2) {
						if(check_hash(second_hash_table, next_state)) 
							return 1;
						++tail;
						queue[tail].move = cur_move + 1;
						queue[tail].state = next_state;
						insert_hash(hash_table, &(queue[tail].state), (queue[tail].state)%PRIME);
					} 
				}
			}
		}
		++second_head;
		cnt = 0;
		cur_state = second_queue[second_head].state;
		second_cur_move = second_queue[second_head].move;
		for(i=0; i<64 && cnt<4; i++) {
			if(cur_state & (((unsigned long long)1)<<i)) {
				++cnt;
				x = i/BOARD;
				y = i%BOARD; 
				for(j=0; j<4; j++) {
					next_x = x + dx[j];
					next_y = y + dy[j];
					if(!is_valid(next_x, next_y))
						continue;
					if(is_set(next_x, next_y, cur_state)) {
						next_x += dx[j];
						next_y += dy[j];
						if(!is_valid(next_x, next_y))
							continue;
					}
					next_state = cur_state;
					clear_bit(x, y, next_state);
					set_bit(next_x, next_y, next_state);
					if(!check_hash(second_hash_table, next_state) && second_cur_move<MOVE_MAX/2) {
						if(check_hash(hash_table, next_state)) 
							return 1;
						++second_tail;
						second_queue[second_tail].move = second_cur_move + 1;
						second_queue[second_tail].state = next_state;
						insert_hash(second_hash_table, &(second_queue[second_tail].state), (second_queue[second_tail].state)%PRIME);
					} 
				}
			}
		}
	}
	return 0;
}

int
main(int argc, char **argv)
{
	int i, j, k;
	while(scanf("%d %d", &i, &j) != EOF) {
		head = second_head = -1;
		tail = second_tail = 0;
		begin = end = 0;
		set_bit(i-1, j-1, begin);
		memset(hash_table, 0, sizeof(hash_table));
		memset(second_hash_table, 0, sizeof(second_hash_table));
		memset(queue, 0, sizeof(queue));
		memset(second_queue, 0, sizeof(second_queue));
		for(k=1; k<4; k++) {
			scanf("%d %d", &i, &j);
			set_bit(i-1, j-1, begin);
		}
		for(k=0; k<4; k++) {
			scanf("%d %d", &i, &j);
			set_bit(i-1, j-1, end);
		}
		printf("%s\n", bfs()==1 ? "YES" : "NO");
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101
#define MAX_MOD 10001
char num[MAX_LEN];
int hash[MAX_MOD];
int mod_arr[MAX_LEN][10];
int k, len, tmp[MAX_LEN], tmp2[MAX_LEN], start_mod;
int head, tail;
struct EACH {
	int digits[MAX_LEN];
	int remainder;
	int index;
} queue[MAX_MOD];

void
init()
{
	int i, j;
	len = strlen(num);
	for(j=0; j<10; j++)
		mod_arr[0][j] = j%k;
	for(i=1; i<len; i++)
		for(j=0; j<10; j++)
			mod_arr[i][j] = (mod_arr[i-1][j]*10)%k;
	start_mod = 0;
	for(i=0; i<len; i++) {
		tmp[i] = tmp2[i] = num[len-i-1]-'0';
		start_mod += (mod_arr[i][num[len-i-1]-'0']);
	}
	start_mod %= k;
	head = -1;
	tail = 0;
	memset(hash, 0, sizeof(hash));
	memset(queue, 0, sizeof(queue));
}

void
bfs()
{
	int i, j, t, cur_rem, cur_index;
	queue[tail].remainder = start_mod;
	memcpy(queue[tail].digits, tmp, sizeof(int)*len);
	queue[tail].index = len-1;
	hash[start_mod] = 1;
	while(head < tail) {
		++head;
		cur_rem = queue[head].remainder;
		cur_index = queue[head].index;
		memcpy(tmp, queue[head].digits, sizeof(int)*len);
		if(cur_rem == 0) {
			for(i=len-1; i>=0; i--)
				printf("%d", tmp[i]);
			printf("\n");
			return;
		}
		/* changing digits: from least (smaller than itself) */
		for(i=cur_index; i>=0; i--) {
			for(j=0; j<tmp2[i]; j++) {
				if(i==len-1 && j==0)
					continue;
				t = cur_rem + mod_arr[i][j] - mod_arr[i][tmp2[i]] + k; /* O(1) to find the new remainder */
				t = t % k;
				tmp[i] = j;
				if(!hash[t]) {
					++tail;
					queue[tail].remainder = t;
					queue[tail].index = i-1;
					memcpy(queue[tail].digits, tmp, sizeof(int)*len);
					hash[t] = 1;
				}
			}
			tmp[i] = tmp2[i];
		}
		/* changing digits: to max (greater than itself) */
		for(i=0; i<=cur_index; i++) {
			for(j=tmp2[i]+1; j<10; j++) {
				t = cur_rem + mod_arr[i][j] - mod_arr[i][tmp2[i]] + k;
				t = t % k;
				tmp[i] = j;
				if(!hash[t]) {
					++tail;
					queue[tail].remainder = t;
					queue[tail].index = i-1;
					memcpy(queue[tail].digits, tmp, sizeof(int)*len);
					hash[t] = 1;
				}
				tmp[i] = tmp2[i];
			}
		}
	}
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%s", num) != EOF) {
		scanf("%d", &k);
		init();
		bfs();
	}
	return 0;
}

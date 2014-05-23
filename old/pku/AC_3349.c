/* Hash & Minimal Representation(ZhouYuan) */
/* Memory: 7020K Time: 3172MS */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PRIME 129997
#define MAX_NUM 150000
#define ARMS 6
struct Node {
	int index;
	struct Node *next;
}hash[MAX_NUM];
long arr[MAX_NUM][ARMS];
long rvs[ARMS], cmpee[ARMS*2], cmper[ARMS*2];
int n;

int 
minimal_representation(long *ee, long *er)
{
	int i, j, k;
	i = j = 0;
	memcpy(cmpee, ee, sizeof(long)*ARMS);
	memcpy(cmper, er, sizeof(long)*ARMS);
	memcpy(cmpee+ARMS, ee, sizeof(long)*ARMS);
	memcpy(cmper+ARMS, er, sizeof(long)*ARMS);
	while(i<=ARMS && j<=ARMS) {
		k = 0;
		while(cmpee[i+k] == cmper[j+k])
			++k;
		if(k >= ARMS)
			return 1;
		else {
			if(cmpee[i+k] > cmper[j+k])
				i = i+k+1;
			else
				j = j+k+1;
		}
	}
	return 0;
}

int
chained_hash_insert(int i, int hash_index)
{
	int k;
	struct Node *cur, *node = hash[hash_index].next;
	while(node != NULL) {
		/* compare */
		if(minimal_representation(arr[i], arr[node->index]))
			return 1;
		for(k=0; k<ARMS; k++)
			rvs[k] = arr[node->index][ARMS-k-1];
		if(minimal_representation(arr[i], rvs))
			return 1;
		node = node->next;
	}
	/* insert at the head */
	cur = malloc(sizeof(struct Node));
	cur->index = i;
	cur->next = hash[hash_index].next;
	hash[hash_index].next = cur;
	return 0;
}

int
main(int argc, char **argv)
{
	int i, j;
	long sum;
	scanf("%d", &n);
	memset(hash, 0, sizeof(hash));
	for(i=0; i<n; i++) {
		sum = 0;
		for(j=0; j<ARMS; j++) {
			scanf("%ld", arr[i]+j);
			sum += arr[i][j];
		}
		/* operation here */
		if(chained_hash_insert(i, sum%PRIME)) {
			printf("Twin snowflakes found.\n");
			exit(0);
		}
	}
	printf("No two snowflakes are alike.\n");
}

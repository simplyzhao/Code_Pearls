/* huffman tree */
/* priority-queue(min-heap) used */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_INT 9223372036854775807
#define PARENT(i) ((i-1)>>1)
#define LEFT_CLD(i) ((i<<1)+1)
#define RIGHT_CLD(i) ((i+1)<<1)
#define SWAP(a, b) a=a+b; b=a-b; a=a-b /* tricky */
int heap_size;

void
min_heapify(long long *heap, int i)
{
	int min = i;
	int left = LEFT_CLD(i);
	int right = RIGHT_CLD(i);
	if(left<heap_size && heap[min]>heap[left])
		min = left;
	if(right<heap_size && heap[min]>heap[right])
		min = right;
	if(min != i) {
		SWAP(heap[i], heap[min]);
		min_heapify(heap, min);
	}
}

void
build_min_heap(long long *heap, int length)
{
	int i;
	heap_size = length;
	for(i=(heap_size>>1)-1; i>=0; i--)
		min_heapify(heap, i);
}

long long
extract_min(long long *heap)
{
	if(heap_size < 1) {
		fprintf(stderr, "heap underflow\n");
		exit(1);
	}
	long long rt = heap[0];
	SWAP(heap[0], heap[heap_size-1]);
	--heap_size;
	min_heapify(heap, 0);
	return rt;
}

void
decrease_key(long long *heap, int i, long long new_key)
{
	int c, p;
	if(heap[i] < new_key) {
		fprintf(stderr, "new key is larger than current key\n");
		exit(1);
	}
	heap[i] = new_key;
    c = i;
	p = PARENT(i);
	while(c>0 && heap[p]>heap[c]) {
		SWAP(heap[c], heap[p]);
		c = p;
		p = PARENT(c);
	}
}

void
insert(long long *heap, long long value)
{
	++heap_size;
	heap[heap_size-1] = MAX_INT;
	decrease_key(heap, heap_size-1, value);
}

long long
huffman_tree_way(long long *heap, int length)
{
	int i;
	long long fst, snd, sum, rt=0;
	build_min_heap(heap, length);
	for(i=0; i<length-1; i++) {
		fst = extract_min(heap);
		snd = extract_min(heap);
		sum = fst + snd;
		rt += sum;
		insert(heap, sum);
	}
	return rt;
}

int
main(int argc, char **argv)
{
	int i, plank_num;
	long long *heap;
	scanf("%d", &plank_num);
	heap = calloc(plank_num, sizeof(long long));
	for(i=0; i<plank_num; i++)
		scanf("%lld", heap+i);
	if(plank_num==1)
		printf("%lld\n", heap[0]);
	else
		printf("%lld\n", huffman_tree_way(heap, plank_num));
	return 0;
}

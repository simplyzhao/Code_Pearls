/* huffman encoding & decoding */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN 26
#define MAX_INPUT_LEN 1001
#define LEFT(index) (((index)<<1)+1)
#define RIGHT(index)  ((index+1)<<1)
#define PARENT(index) ((index-1)>>1)
struct Node {
	char c;
	int weight;
	struct Node *left, *right;
};
struct Node *heap_array[LEN];
int heap_size, num;
int count[LEN];

/* START: priority queue implementation */
void
swap(struct Node **harr, int i, int j)
{
	struct Node *tmp = harr[i];
	harr[i] = harr[j];
	harr[j] = tmp;
}

void
min_heapify(int index) 
{
	int smallest = index;
	if(LEFT(index)<heap_size && heap_array[LEFT(index)]->weight<heap_array[smallest]->weight)
		smallest = LEFT(index);
	if(RIGHT(index)<heap_size && heap_array[RIGHT(index)]->weight<heap_array[smallest]->weight)
		smallest = RIGHT(index);
	if(smallest != index) {
		swap(heap_array, index, smallest);
		min_heapify(smallest);
	}
}

void
build_heap()
{
	int i;
	for(i=heap_size>>1; i>=0; i--)
		min_heapify(i);
}

struct Node *
extract_min()
{
	if(heap_size<=0)
		return NULL;
	struct Node *ret = heap_array[0];
	heap_array[0] = heap_array[heap_size-1];
	--heap_size;
	min_heapify(0);
	return ret;
}

void
heap_insert(struct Node *node)
{
	heap_array[heap_size++] = node;
	int index = heap_size-1;
	while(PARENT(index)>=0 && heap_array[index]->weight<=heap_array[PARENT(index)]->weight) { 
		swap(heap_array, index, PARENT(index));
		index = PARENT(index);
	}
}
/* END: priority queue implementation */

void
init(char *str, int len)
{
	int i;
	char *lp = str;
	struct Node *node;
	heap_size = 0;
	memset(count, 0, sizeof(count));
	while(*lp) {
		++count[(*lp)-'a'];
		++lp;
	}

	for(i=0; i<LEN; i++) {
		if(count[i]) {
			node = (struct Node *)malloc(sizeof(struct Node));
			node->c = i+'a';
			node->weight = count[i];
			node->left = node->right = NULL;
			heap_array[heap_size++] = node;
		}
	}
	num = heap_size; /* total number of characters */
	build_heap();
}

struct Node *
build_huffman_tree()
{
	int i;
	struct Node *arg1, *arg2, *node;
	for(i=1; i<num; i++) {
		arg1 = extract_min();
		arg2 = extract_min();
		node = (struct Node *)malloc(sizeof(struct Node));
		node->c = 0; /* non-leaf */
		node->weight = arg1->weight + arg2->weight;
		node->left = arg1;
		node->right = arg2;
		heap_insert(node);
	}
	struct Node *ret = extract_min();
	return ret;
}

void
find_char_encoding(struct Node *root, int depth, char *ret)
{
	if(root->left==NULL && root->right==NULL) {
		printf("%c: %s\n", root->c, ret);
		return;
	}
	ret[depth] = '0';
	find_char_encoding(root->left, depth+1, ret);
	ret[depth] = '\0';
	ret[depth] = '1';
	find_char_encoding(root->right, depth+1, ret);
	ret[depth] = '\0';
}

void
free_huffman_tree(struct Node *root)
{
	if(root == NULL)
		return;
	free_huffman_tree(root->left);
	free_huffman_tree(root->right);
	free(root);
}

void
test_print_tree(struct Node *root)
{
	if(root == NULL)
		return;
	test_print_tree(root->left);
	printf("%c:%d\n", root->c==0?'X':root->c, root->weight);
	test_print_tree(root->right);
}

int
main(int argc, char **argv)
{
	char buf[MAX_INPUT_LEN], enc[LEN*2];
	while(scanf("%s", buf) != EOF) {
		memset(enc, 0, sizeof(enc));
		init(buf, strlen(buf));
		struct Node *root = build_huffman_tree();
		find_char_encoding(root, 0, enc);
		free_huffman_tree(root);
	}
}

/* inversions(can be calculated in mergesort) */
/* including three solutions here */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NUM 100
#define MAX_LEN 50
struct Elem {
	char str[MAX_LEN+1];
	int index;
}seq[MAX_NUM];
int m, n;

/* O(n^2) Time: 16MS */
int
inversion_cal(char *str)
{
	int i, j, count = 0;
	int len = strlen(str);
	for(i=0; i<len; i++)
		for(j=i+1; j<len; j++)
			if(str[i] > str[j])
				++count;
	return count;
}

static void
merge(char *str, int begin, int mid, int end, int *count)
{
	char *first, *second;
	int first_num = mid-begin+1;
	int second_num = end-mid;
	int i, j, k;
	first = calloc(first_num, sizeof(char));
	second = calloc(second_num, sizeof(char));
	memcpy(first, str+begin, first_num*sizeof(char));
	memcpy(second, str+mid+1, second_num*sizeof(char));

	i = j = 0;
	k = begin;
	while(i<first_num && j<second_num) {
		if(first[i] <= second[j]) {
			str[k++] = first[i++];
			*count += j;
		} else
			str[k++] = second[j++];
	}
	if(i == first_num)
		for( ; j<second_num; j++)
			str[k++] = second[j];
	else
		for( ; i<first_num; i++) {
			str[k++] = first[i];
			if(first[i] > second[j-1])
				*count += j;
		}
	
	free(first);
	free(second);
}

static void
merge_sort(char *str, int begin, int end, int *count)
{
	if(begin >= end)
		return;
	int mid = (begin+end)/2;
	merge_sort(str, begin, mid, count);
	merge_sort(str, mid+1, end, count);
	merge(str, begin, mid, end, count);
}

/* O(nlgn) Time: 532MS*/
int
inversion_cal1(char *str)
{
	int count = 0;
	char temp[MAX_LEN+1];
	strcpy(temp, str);
	merge_sort(temp, 0, strlen(temp)-1, &count);
	return count;
}

/* O(n) Time: 16MS */
int 
inversion_cal2(char *str)
{
	int i, temp[4], count = 0;
	int len = strlen(str);
	memset(temp, 0, sizeof(temp));
	for(i=len-1; i>=0; i--) {
		switch(str[i]) {
			case 'A':
				++temp[0];
				break;
			case 'C':
				++temp[1];
				count += temp[0];
				break;
			case 'G':
				++temp[2];
				count += (temp[0]+temp[1]);
				break;
			case 'T':
				++temp[3];
				count += (temp[0]+temp[1]+temp[2]);
				break;
		}
	}
	return count;
}

int
inversion_compare(const void *arg1, const void *arg2)
{
	int inv1 = inversion_cal1(((struct Elem *)arg1)->str);
	int inv2 = inversion_cal1(((struct Elem *)arg2)->str);
	if(inv1 == inv2)
		return ((struct Elem *)arg1)->index - ((struct Elem *)arg2)->index;
	else
		return inv1 - inv2;
}

int
main(int argc, char **argv)
{
	int i;
	while(scanf("%d %d", &n, &m) != EOF) {
		for(i=0; i<m; i++) {
			scanf("%s", seq[i].str);
			seq[i].index = i;
		}
		qsort(seq, m, sizeof(struct Elem), inversion_compare);
		for(i=0; i<m; i++)
			printf("%s\n", seq[i].str);
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 5001
struct Rec {
	int x_min, y_min;
	int x_max, y_max;
} recs[MAX_LEN];
int num;

/* sort according to 'be covered' */
int
compare(const void *arg1, const void *arg2)
{
	int rt;
	struct Rec *rec_1 = (struct Rec *)arg1;
	struct Rec *rec_2 = (struct Rec *)arg2;
	if((rt=(rec_2->x_min - rec_1->x_min)) == 0) 
		if((rt=(rec_1->x_max - rec_2->x_max)) == 0) 
			if((rt=(rec_2->y_min - rec_1->y_min)) == 0) 
				rt=(rec_1->y_max - rec_2->y_max);
	return rt;
}

int
within(struct Rec *rec_1, struct Rec *rec_2)
{
	if(rec_1->x_min<=rec_2->x_min && rec_1->x_max>=rec_2->x_max && rec_1->y_min<=rec_2->y_min && rec_1->y_max>=rec_2->y_max)
		return 1;
	return 0;
}

int
main(int argc, char **argv)
{
	int i, j, cnt;
	while(scanf("%d", &num)!=EOF) {
		cnt = 0;
		for(i=0; i<num; i++)
			scanf("%d %d %d %d", &(recs[i].x_min), &(recs[i].x_max), &(recs[i].y_min), &(recs[i].y_max));
		qsort(recs, num, sizeof(struct Rec), compare);
		for(i=0; i<num; i++) {
			if(i!=0 && within(recs+i-1, recs+i)) {
				++cnt;
				continue;
			}
			for(j=i+1; j<num; j++) {
				if(within(recs+j, recs+i)) {
					++cnt;
					break;
				}
			}
		}
		printf("%d\n", cnt);
	}
}

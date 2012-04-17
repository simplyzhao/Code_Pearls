/* DP */
/* see: http://www.cppblog.com/AClayton/archive/2007/09/14/32185.html */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VALUE_MAX 6
int num[VALUE_MAX+1];
int can_reach[60005];
int value_sum, value_half;

int
dp()
{
	int i, j, k, temp, cur_max = 0;
	can_reach[0] = 1;
	for(i=1; i<=VALUE_MAX; i++) {
		if(num[i] > 0) {
			for(j=cur_max; j>=0; j--) { /* tricky */
				if(can_reach[j]) {
					for(k=1; k<=num[i]; k++) {
						temp = i*k+j;
						if(temp == value_half)
							return 1;
						if(temp>value_half) /*  initial: if(temp>value_half || can_reach[temp]) break; */
							break;
						can_reach[temp] = 1;
					}
				}
			}
		}
		cur_max += (i*num[i]);
		if(cur_max>value_half)
			cur_max = value_half;
	}
}

int
main(int argc, char **argv)
{
	int i, tc=0;
	while(1) {
		++tc;
		value_sum = 0;
		memset(can_reach, 0, sizeof(can_reach));
		for(i=1; i<=VALUE_MAX; i++) {
			scanf("%d", num+i);
			value_sum += (i*num[i]);
		}
		if(value_sum == 0)
			break;
		value_half = (value_sum >> 1);
		if(value_sum%2 != 0)
			printf("Collection #%d:\n%s\n\n", tc, "Can't be divided.");
		else
			printf("Collection #%d:\n%s\n\n", tc, (dp()==1)?"Can be divided.":"Can't be divided.");
	}
	return 0;
}

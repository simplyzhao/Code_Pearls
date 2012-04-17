#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 200
int corridor[N];

int
main(int argc, char **argv)
{
	int temp, tests, num, i, j, s, t, max;
	scanf("%d", &tests);
	while(tests--) {
		max = 0;
		memset(corridor, 0, sizeof(int)*N);
		scanf("%d", &num);
		for(i=0; i<num; i++) {
			scanf("%d %d", &s, &t);
			if(s > t) {
				temp = s;
				s = t;
				t = temp;
			}
			s = (s-1)>>1;
			t = (t-1)>>1;
			for(j=s; j<=t; j++)
				++corridor[j];
		}
		for(j=0; j<N; j++)
			if(max < corridor[j])
				max = corridor[j];
		printf("%d\n", max*10);
	}
	return 0;
}

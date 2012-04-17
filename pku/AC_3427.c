#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 30001
#define INF 0x7FFFFFFF
int N, L;
int length[MAX_LEN];
int mwaste, myear;

int
main(int argc, char **argv)
{
	int i, cyear, cwaste;
	while(scanf("%d %d", &N, &L) != EOF) {
		for(i=0; i<N; i++)
			scanf("%d", length+i);
		mwaste = myear = INF;

		for(cyear=0; cyear<L; cyear++) {
			cwaste = 0;
			for(i=0; i<N; i++)
				cwaste += ((length[i]+cyear)%L);
			if(cwaste < mwaste) {
				mwaste = cwaste;
				myear = cyear;
			}
			if(mwaste == 0)
				break;
		}

		printf("%d\n", myear);
	}
}

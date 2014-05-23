/*
 * Problem:
 * given an upper bound like U(integer), print all the primes between 0-U
 *
 * Points:
 * this's a O(n) algorithm, amazing...
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 250000
int N, hash[MAX_N];
int pcount, primes[MAX_N];

void
linear_selection()
{
	int i, j;
	primes[pcount++] = 1;
	for(i=2; i<=N; i++) {
		if(!hash[i])
			primes[pcount++] = i;
		for(j=1; j<pcount && i*primes[j]<=N; j++) {
			hash[i*primes[j]] = 1;
			if(i%primes[j] == 0)
				break;
		}
	}
}

int
main(int argc, char **argv)
{
	int i;
	while(1) {
		printf("Enter the upper boundary: ");
		scanf("%d", &N);
		if(!N)
			break;
		memset(hash, 0, sizeof(hash));
		pcount = 0;
		linear_selection();
		for(i=0; i<pcount; i++)
			printf("%d\n", primes[i]);
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_LEN 350 
int primes[MAX_LEN];
int count;
int n, c;

int
is_prime(int num)
{
	int i, t=(int)sqrt(num*1.0);
	for(i=2; i<=t; i++)
		if(num%i == 0)
			return 0;
	return 1;
}

void
init()
{
	int i;
	count = 2;
	primes[0] = 1;
	primes[1] = 2;
	for(i=3; i<=1101; i++)
		if(is_prime(i))
			primes[count++] = i;
}

void
output()
{
	int i, out_num, begin, end, total=0;
	while(primes[total]<=n)
		++total;
	out_num = total%2==0 ? 2*c : (2*c-1);
	if(out_num >= total) {
		begin = 0;
		end = total-1;
	} else {
		begin = (total-out_num)/2;
		end = begin+out_num-1;
	}
	printf("%d %d:", n, c);
	for(i=begin; i<=end; i++)
		printf(" %d", primes[i]);
	printf("\n\n");
}

int
main(int argc, char **argv)
{
	init();
	while(scanf("%d %d", &n, &c)!=EOF) {
		output();
	}
}

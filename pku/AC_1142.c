#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int num;

int
is_prime(int n)
{
	int i, bound = (int)sqrt((double)n);
	for(i=2; i<=bound; i++)
		if(n%i == 0)
			return 0;
	return 1;
}

int 
bit_sum(int n)
{
	int sum = 0;
	while(n > 0) {
		sum += (n%10);
		n /= 10;
	}
	return sum;
}

int
is_satisfy(int n)
{
	int sum, psum, div;
	sum = bit_sum(n); /* for initial number */
	psum = 0;
	while(1) {
		if(is_prime(n)) {
			psum += bit_sum(n);
			break;
		}
		div = 2;
		while(n%div != 0)
			++div;
		n = n/div;
		psum += bit_sum(div);
	}
	return sum==psum;
}

void
solve()
{
	while(1) {
		++num;
		if(is_prime(num))
			continue;
		if(is_satisfy(num))
			break;
	}
	printf("%d\n", num);
}

int
main(int argc, char **argv)
{
	while(scanf("%d", &num)!=EOF && num) {
		solve();
	}
}

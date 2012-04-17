/*
 * Problem:
 * given an number, count its 1-bits in binary form(non-loop)
 */
#include<stdio.h>
#include<stdlib.h>

int 
count_1_bits_recursive(int num)
{
	if(num == 0)
		return 0;
	else
		return (num & 1) + count_1_bits_recursive(num>>1);
}

int
count_1_bits_tricky(int num)
{
	int count = 0;
	while(num > 0) {
		count++;
		/*
		 * 每执行一次num=num&(num-1)，会将num二进制最右边的一个1变为0
		 */
		num = num & (num-1);
	}
	return count;
}

/* -------------------test---------------- */
int
main(int argc, char **argv)
{
	int num;
	if(argc != 2) {
		fprintf(stderr, "Usage: a.out <number>\n");
		exit(1);
	}

	num = atoi(argv[1]);
	printf("1-bits: %d\n", count_1_bits_recursive(num));
	printf("1-bits(tricky): %d\n", count_1_bits_tricky(num));

	return 0;
}

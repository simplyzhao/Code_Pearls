/*
 * Problem:
 * given you the coins, and the total amount of money to change, find a solution
 * for this change which minimize the number of coins needed.
 *
 * Example:
 * coins[] = {1, 5, 10, 21, 25};
 * money = 19;
 * solution[] = {10, 5, 1, 1, 1, 1};
 *
 * Points:
 * Dynamic Programming
 * Greey Algorithm here is usually uncorrect
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_COINS 10
#define MAX_MONEY 32767
#define INF 0x7FFFFFFF
int coins_num, coins[MAX_COINS];
int total, changes_num[MAX_MONEY], changes[MAX_MONEY];

int
is_continue()
{
	char ch[2];
	while(1) {
		printf("Are you gonna continue this game(Y if yes, or N)?\n");
		scanf("%s", ch);
		if(ch[0] == 'Y' || ch[0] == 'y')
			return 1;
		else if(ch[0] == 'N' || ch[0] == 'n')
			return 0;
	}
}

void
input()
{
	int i;
	printf("Enter the number of coins: ");
	scanf("%d", &coins_num);
	printf("Enter the amount of coins(ascending order, separated by space): \n");
	for(i=0; i<coins_num; i++)
		scanf("%d", coins+i);
	printf("Enter the amount of money to change: ");
	scanf("%d", &total);
}

void
output()
{
	int i, tmp;
	printf("Solution: \n");
	printf("Minimum number of coins needed: %d\n", changes_num[total]);
	printf("Coins: \n");
	tmp = total;
	while(tmp > 0) {
		printf("%d ", changes[tmp]);
		tmp -= changes[tmp];
	}
	printf("\n");
}

/*
 * Dynamic Programming: f(m) = min (f[m-coins[i] + 1)
 * O(N*K), N is the number of coins, K is the total amount of money to change
 */
void 
solve()
{
	int i, j, k, min;
	changes_num[0] = 0;
	for(i=1; i<=total; i++) { /* Money: from '1' to 'total' */
		min = INF;
		k = -1;
		for(j=0; j<coins_num; j++) { /* Coins: ascending, and always contains '1' */
			if(i >= coins[j]) {
				if(min > changes_num[i-coins[j]]+1) {
					min = changes_num[i-coins[j]]+1;
					k = j;
				}
			} else
				continue;
		}
		changes_num[i] = min;
		changes[i] = coins[k];
	}
}

int
main(int argc, char **argv)
{
	while(is_continue()) {
		input();
		solve();
		output();
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int player, dealer;
int n, count[14];
char card[3][2];

int
score(char ch)
{
	if(ch == 'A')
		return 11;
	else if(ch == 'T' || ch=='J' || ch=='Q' || ch=='K')
		return 10;
	else
		return ch-'0';
}

int
main(int argc, char **argv)
{
	int i, tmp, total;
	while(scanf("%d", &n)!=EOF && n) {
		total = player = dealer = 0; memset(count, 0, sizeof(count));
		for(i=0; i<3; i++) {
			scanf("%s", card[i]);
			tmp = score(card[i][0]);
			++count[tmp];
			if(i == 0)
				dealer += tmp;
			else
				player += tmp;
		}
		if(player == 22) /* two Ace */
			player = 12;
		for(i=2; i<=11; i++) {
			if((dealer+i==22 ? 12 : dealer+i) < player) {
				if(i == 10)
					total += (4*4*n-count[i]);
				else
					total += (4*n-count[i]);
			}
		}
		printf("%.3f%%\n\n", ((double)total)/(52*n-3)*100);
	}
}

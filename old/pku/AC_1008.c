#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const char haab_mons[19][10] = {
	"pop","no","zip","zotz","tzec","xul","yoxkin","mol","chen","yax","zac","ceh","mac","kankin","muan","pax","koyab","cumhu","uayet"};
const char tzo_days[20][10] = {
	"imix","ik","akbal","kan","chicchan","cimi","manik","lamat","muluk","ok","chuen","eb","ben","ix","mem","cib","caban","eznab","canac","ahau"};

int
input()
{
	int day, m, year;
	char month[10];
	scanf("%d. %s %d", &day, month, &year);
	for(m=0; m<19; m++)
		if(strcmp(haab_mons[m], month) == 0)
			break;
	return year*365 + m*20 + day;
}

void
output(int num)
{
	printf("%d %s %d\n", 1+num%13, tzo_days[(num)%20], num/260);
}

int
main(int argc, char **argv)
{
	int i, tests, num;
	scanf("%d", &tests);
	printf("%d\n", tests);
	while(tests--) {
		num=input();
		output(num);
	}
	return 0;
}

/* Calendar Type Problem [classic] */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char days[][10] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
};
int months_normal[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int months_leap[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int diffs[] = {365, 366};
int *m_points[] = {months_normal, months_leap};

int
LEAP_YEAR(int year)
{
	if((year%4==0&&year%100!=0) || (year%400==0))
		return 1;
	return 0;
}

int
main(int argc, char **argv)
{
	long num, temp;
	int year, month;
	int i, index, cur_m;
	while(scanf("%ld", &num)!=EOF && num!=-1) {
		year = 2000;
		month = 1;
		index = LEAP_YEAR(year);
		temp = num;
		while(num >= diffs[index]) {
			num -= diffs[index];
			++year;
			index = LEAP_YEAR(year);
		}
		i = 0;
		cur_m = (*(m_points[index]+i));
		while(num >= cur_m) {
			num -= cur_m;
			++i;
		    cur_m = (*(m_points[index]+i));
		}
		printf("%d-%02d-%02ld %s\n", year, i+1, num+1, days[((temp)+6)%7]);
	}
}

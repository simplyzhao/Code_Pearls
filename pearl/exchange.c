/* 问题: 有一个由大小写组成的字符串,对它进行修改,将其中的所有小写字母排在大写字母的前面 */
/* 解题思路:
 * 1.
 * 设置两个指针，一个从前向后移动，指向第一个大写字母；一个从后向前移动，指向最后一个小写字母
 * 2.
 * 设置两个指针，都是从前向后移动，一个每次移动一步，另一个只有在交换时才移动
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 101

char *
exchange1(char *str, int len)
{
	char *ptr1 = str;
	char *ptr2 = str + len -1;
	while(ptr1<=ptr2 && ptr1<str+len && ptr2>=str) {
		while(*ptr1>='a' && *ptr1<='z')
			++ptr1;
		while(*ptr2>='A' && *ptr2<='Z')
			--ptr2;
		if(ptr1<=ptr2) {
			*ptr1 = *ptr1 ^ *ptr2;
			*ptr2 = *ptr1 ^ *ptr2;
			*ptr1 = *ptr1 ^ *ptr2;
		}
	}
	return str;
}

char *
exchange2(char *str, int len)
{
	char *ptr1, *ptr2;
	ptr1 = ptr2 = str;
	for( ; ptr2<str+len; ptr2++) {
		if(*ptr2>='a' && *ptr2<='z') {
			if(ptr1 != ptr2) {
				*ptr1 = *ptr1 ^ *ptr2;
				*ptr2 = *ptr1 ^ *ptr2;
				*ptr1 = *ptr1 ^ *ptr2;
			}

			++ptr1;
		}
	}
	return str;
}

int
main(int argc, char **argv)
{
	char buf[MAX_LEN], buf_dup[MAX_LEN];
	while(scanf("%s", buf) != EOF) {
		strcpy(buf_dup, buf);
		printf("%s\n", exchange1(buf, strlen(buf)));
		printf("%s\n", exchange2(buf_dup, strlen(buf_dup)));
	}
	return 0;
}

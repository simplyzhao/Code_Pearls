/* Time: 1938MS, Oh, God */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TEMP_MAX 100
#define MAX_NUM 100000
char *phones[MAX_NUM];
                    /* A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z */
const char mapping[] = {'2','2','2','3','3','3','4','4','4','5','5','5','6','6','6','7','0','7','7','8','8','8','9','9','9','0'};
const char *hyphen = "-";
int num;

void
map_hyphen(char *str, int len)
{
	int i, index = 0; 
	char tmp[TEMP_MAX];
	/*
	char *p, *q;
	*/
	strcpy(tmp, str);
	for(i = 0; i<len; i++) {
		if(tmp[i]=='-')
			continue;
		else if(tmp[i]>='A' && tmp[i]<='Z')
			str[index] = mapping[tmp[i]-'A'];
		else
			str[index] = tmp[i];
		++index;
	}
	str[index] = '\0';
	/*
	 * TLE
	strcpy(tmp, str);
	q = str;
	p = strtok(tmp, hyphen);
	while(p) {
		strcpy(q, p);
		q += strlen(p);
		p = strtok(NULL, hyphen);
	}
	if(q != str)
		*q = '\0';
	*/
}

int
compare(const void *arg1, const void *arg2)
{
	return strcmp((*(char **)arg1), (*(char **)arg2));
}

void
print(char *str, int count)
{
	char ch = str[3];
	str[3] = '\0';
	printf("%s-", str);
	str[3] = ch;
	str += 3;
	printf("%s %d\n", str, count);
}

void 
output()
{
	int i, j, count, flag = 0;
	char *p;
	qsort(phones, num, sizeof(char *), compare);
	i = count = 0;
	while(i < num) {
		p = phones[i];
		count += 1;
		for(j=i+1; j<num; j++) {
			if(strcmp(p, phones[j]) == 0)
				count+=1;
			else
				break;
		}
		if(count > 1) {
			print(phones[i], count);
			flag += 1;
		}
		i = j;
		count = 0;
	}
	if(!flag)
		printf("No duplicates.\n"); /* at first, "No duplicates\n", caused WA */
}

int
main(int argc, char **argv)
{
	int i, len;
	char str[TEMP_MAX];
	scanf("%d", &num);
	for(i=0; i<num; i++) {
		scanf("%s", str);
		len = strlen(str);
		phones[i] = malloc(sizeof(char)*(len+1));
		strcpy(phones[i], str);
		/* do stuff here */
		map_hyphen(phones[i], len);
	}
	output();
	for(i=0; i<num; i++)
		free(phones[i]);
}

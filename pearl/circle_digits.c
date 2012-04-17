/* 问题: 两整数相除，求循环节 */
/* 分析:
 * 模拟整数相除的步骤，记录每次的商、余，当余重复时即发现循环节 
 * 余的范围为[0, 被除数)，因此记录数组的大小可根据被除数确定
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void
get_circle_digits(unsigned int a, unsigned int b)
{
	int i, mod, tmp, index = 0;
	int *div = (int *)malloc(sizeof(int) * b);
	int *mod_pos = (int *)malloc(sizeof(int) * b);
	memset(mod_pos, -1, sizeof(int)*b);
	mod = a = a%b;
	while(1) {
		if(mod==0 || mod_pos[mod]!=-1)
			break;
		mod_pos[mod] = index;
		tmp = mod*10;
		div[index] = tmp / b;
		mod = tmp % b;
		++index;
	}
	if(mod == 0) 
		printf("No Circle\n");
	else {
		printf("0.");
		for(i=0; i<mod_pos[mod]; i++)
			printf("%d", div[i]);
		printf("(");
		for(i=mod_pos[mod]; i<index; i++)
			printf("%d", div[i]);
		printf(")");
		printf("\n");
	}
}

int
main(int argc, char **argv)
{
	unsigned int a, b;
	while(scanf("%u %u", &a, &b) != EOF) {
		get_circle_digits(a, b);
	}
	return 0;
}

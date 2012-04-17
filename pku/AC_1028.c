/*
 * just using one array, ^-^
 * The problem says two stacks should be used
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN_MAX 71
#define NUM_MAX 100
#define CMD_MAX 8
#define QUIT "QUIT"
#define FORWARD "FORWARD"
#define VISIT "VISIT"
#define BACK "BACK"
#define IGN "Ignored"
char cmd[CMD_MAX];
char addr[LEN_MAX];
char arr[NUM_MAX][LEN_MAX];
int cur_pos, bk_pos, fw_pos;
int can_fw_count;

int 
main(int argc, char **argv)
{
	cur_pos = can_fw_count = 0;
	bk_pos = fw_pos = -1;
	strcpy(arr[cur_pos], "http://www.acm.org/");
	while(scanf("%s", cmd)!=EOF && strcmp(cmd, QUIT)!=0) {
		if(strcmp(cmd, VISIT)==0) {
			scanf("%s", addr);
			strcpy(arr[++cur_pos], addr);
			bk_pos = cur_pos - 1;
			can_fw_count = 0;
			printf("%s\n", arr[cur_pos]);
		} else if(strcmp(cmd, BACK)==0) {
			if(bk_pos == -1)
				printf("%s\n", IGN);
			else {
				fw_pos = cur_pos;
				cur_pos = bk_pos;
				bk_pos = cur_pos-1;
				++can_fw_count;
				printf("%s\n", arr[cur_pos]);
			}
		} else if(strcmp(cmd, FORWARD)==0) {
			if(fw_pos == -1 || !can_fw_count)
				printf("%s\n", IGN);
			else {
				bk_pos = cur_pos;
				cur_pos = fw_pos;
				fw_pos = cur_pos+1;
				--can_fw_count;
				printf("%s\n", arr[cur_pos]);
			}
		}
	}
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 500000
int arr[MAX_SIZE+1];
char visited[3020000];

int
main(int argc, char **argv)
{
	int i, k;
	memset(visited, 0, sizeof(visited));
	arr[0] = 0;
	visited[0] = 1;
	for(i=1; i<=MAX_SIZE; i++) {
		if(arr[i-1]-i>0 && visited[arr[i-1]-i]==0) 
			arr[i] = arr[i-1]-i;
		else
			arr[i] = arr[i-1]+i;
		visited[arr[i]] = 1;
	}
	while((scanf("%d", &k)!=EOF) && (k!=-1))
		printf("%d\n", arr[k]);
}

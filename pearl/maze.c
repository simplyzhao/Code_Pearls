/*
 * Problem:
 * given a maze represented by a two-dimensional array, find all the paths
 * from entrance(array[0][0]) to exit(array[N-1][N-1])
 *
 * Points: backtracking algorithm (recursive)
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAZE_SIZE 4
int maze[MAZE_SIZE][MAZE_SIZE];
int visited[MAZE_SIZE][MAZE_SIZE];
int count;

void
maze_solutions(int (*maze)[MAZE_SIZE], int i, int j)
{
	if(i==MAZE_SIZE-1 && j==MAZE_SIZE-1) {
		++count;
		int p, q;
		//incorrect here, lost the visited sequence
		for(p=0; p<MAZE_SIZE; p++)
			for(q=0; q<MAZE_SIZE; q++) {
				if(visited[p][q] == 1)
					printf("(%d, %d)\t", p, q);
			}
		printf("\n");
		return;
	}
	else {
		/*
		 * 好好理解
		 * 这里把每次递归调用前后的visited修改放到了最外层
		 * 效果相同
		 */
		visited[i][j] = 1;
		if(j<MAZE_SIZE-1 && visited[i][j+1]==0 && maze[i][j+1]==1) { //right
			//visited[i][j+1] = 1;
			maze_solutions(maze, i, j+1);
			//visited[i][j+1] = 0;
		}
		if(j>0 && visited[i][j-1]==0 && maze[i][j-1]==1) { //left
			//visited[i][j-1] = 1;
			maze_solutions(maze, i, j-1);
			//visited[i][j-1] = 0;
		}
		if(i>0 && visited[i-1][j]==0 && maze[i-1][j]==1) { //up
			//visited[i-1][j] = 1;
			maze_solutions(maze, i-1, j);
			//visited[i-1][j] = 0;
		}
		if(i<MAZE_SIZE-1 && visited[i+1][j]==0 && maze[i+1][j]==1) { //down
			//visited[i+1][j] = 1;
			maze_solutions(maze, i+1, j);
			//visited[i+1][j] = 0;
		}
		visited[i][j] = 0;
	}
}

/* -------------------test---------------------- */
int
main(int argc, char **argv)
{
	int i, j;
	count = 0;
	memset(visited, 0, sizeof(int)*MAZE_SIZE*MAZE_SIZE);
	for(i=0; i<MAZE_SIZE; i++)
		for(j=0; j<MAZE_SIZE; j++)
			scanf("%d", &maze[i][j]);

	maze_solutions(maze, 0, 0);
	printf("\nTotal Solutions: %d\n", count);

	return 0;
}

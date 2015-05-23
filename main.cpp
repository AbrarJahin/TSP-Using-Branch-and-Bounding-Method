#include <stdio.h>
#include <unistd.h>		/* find current location */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <string.h>     /* strcat */
#include <math.h>		/* math calc */

#define INPUT_FILE_NAME	"input.txt"
#define MAX_NO_OF_INPUT	10
#define MAX_DISTANCE	999

int cost_matrix[MAX_NO_OF_INPUT][MAX_NO_OF_INPUT],visited[MAX_NO_OF_INPUT],total_input,minimum_cost=0;

void	fileInput();
void	userInput();
void	printInput();
int		findMinValue(int c);
void	mincostCalculation(int city);
void	putMincost();

int main()
{
	//userInput();
	fileInput();
	printInput();
	printf("\n\nThe Path is:\n\n");

	//Time calculation Start
	clock_t t;
	t = clock();
	////////////////////////

	mincostCalculation(0);
	putMincost();

	//Time calculation End
	t = clock() - t;
	//printf ("It took %f second(s).\n",((float)t)/CLOCKS_PER_SEC);
	printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	////////////////////////

	getchar();
	return 0;
}

void fileInput()
{
	FILE *fp;
	//Get Current Directory
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)	//Directory not found
	{
		perror("getcwd() error - Current directory not found !!");
		exit(0);
	}
	strcat(cwd, "\\");
	strcat(cwd, INPUT_FILE_NAME);
	fp = fopen(cwd , "r");

	fscanf(fp,"%d",&total_input);
	for(int i=0;i<total_input;i++)
		for(int j=0;j<total_input;j++)
			fscanf(fp,"%d",&cost_matrix[i][j]);
}

void userInput()
{
	int i,j;
	printf("\n\nEnter Number of Cities: ");
	scanf("%d",&total_input);

	printf("\nEnter Cost Matrix: \n");
	for( i=0;i<total_input;i++)
	{
		printf("\n Enter Elements of Row # : %d\n",i+1);
		for( j=0;j<total_input;j++)
			scanf("%d",&cost_matrix[i][j]);
		visited[i]=0;
	}
}

void printInput()
{
	int i,j;
	printf("\n\nThe Cost Matrix is:\n");

	for( i=0;i<total_input;i++)
	{
		printf("\n\n");
		for( j=0;j<total_input;j++)
		printf("\t%d",cost_matrix[i][j]);
	}
}

void putMincost()
{
	printf("\n\nMinimum cost:");
	printf("%d\n",minimum_cost);
}

void mincostCalculation(int city)
{
	int i,ncity;
	visited[city]=1;
	printf("%d ===> ",city+1);
	ncity=findMinValue(city);
	if(ncity==999)
	{
		ncity=0;
		printf("%d",ncity+1);
		minimum_cost+=cost_matrix[city][ncity];
		return;
	}
	mincostCalculation(ncity);
}

int findMinValue(int c)
{
	int i,nc=MAX_DISTANCE;
	int min=MAX_DISTANCE,kmin;
	for(i=0;i<total_input;i++)
	{
		if((cost_matrix[c][i]!=0)&&(visited[i]==0))
			if(cost_matrix[c][i]<min)
			{
				min=cost_matrix[i][0]+cost_matrix[c][i];
				kmin=cost_matrix[c][i];
				nc=i;
			}
	}

	if(min!=MAX_DISTANCE)
		minimum_cost+=kmin;
	return nc;
}

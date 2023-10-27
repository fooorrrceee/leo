#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *f=fopen("input_data.txt","r");
	int n,e,s,d,c;
	fscanf(f,"%d",&n);
	int cost[n][n],distance[n][n];
	printf("Number of nodes = %d\n",n);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==j)
			{
				cost[i][j]=0;
				distance[i][j]=0;
			}
			else
			{
				cost[i][j]=999;
				distance[i][j]=999;
			}
		}
	}
	fscanf(f,"%d",&e);
	printf("Number of edges = %d\n",e);
	
	for(int i=0;i<e;i++)
	{
		fscanf(f,"%d %d %d",&s,&d,&c);
		cost[s][d]=c;
		cost[d][s]=c;
	}
	
	char temp[10];
	for(int i=0;i<n;i++)
	{
		printf("For node: %d\n",i);
		for(int j=0;j<n-1;j++)
		{
			fseek(f,0,SEEK_SET);
			//ignore first two lines
			fgets(temp,10,f);
			fgets(temp,10,f);
			int flag=0;
			for(int k=0;k<e;k++)
			{
				
				fscanf(f,"%d %d %d",&s,&d,&c);
				if(distance[i][s]+cost[s][d] <distance[i][d])
				{
					flag=1;
					distance[i][d]=distance[i][s]+cost[s][d];
				}
				if(distance[i][d]+cost[d][s] <distance[i][s])
				{
					flag=1;
					distance[i][s]=distance[i][d]+cost[d][s];
				}
			}
			if(flag==1)
			{
				printf("Round %d:\n",j);
				for (int l=0;l<n;l++)
				{
					printf("%d ",distance[i][l]);
				}
				printf("\n\n");
			}
		}
	}
	printf("FINAL ROUTING TABLE:\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%d ",distance[i][j]);
		}
		printf("\n");
	}
	fclose(f);
	return 0;
}

				
































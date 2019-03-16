#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <queue>
#include <string.h>
#include <limits.h>
using namespace std;
struct GRAPH
{
	int M;
	int **maTrix;
};
void initialGraph(GRAPH g)
{
	g.M = 0;
}
int checkConnectedVertex(GRAPH g)
{
	for (int i = 0; i < g.M; i++)
	{
		for (int j = 0; j < g.M; j++)
		{
			if (g.maTrix[i][j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}
int *countComponentsConnected (int *a, int n)
{
	int *b = new int[n];
	for (int i = 1; i <= n; i++)
	{
		int count = 0;
		for (int j = 0; j < n; j++)
		{
			if (i == a[j])
			{
				count++;
			}
		}
		b[i] = count;
	}
	return b;
}
void sortComponentsConnected(int *a,int n)
{
	
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			if (a[i]> a[j] && (a[i] != 0 && a[j] != 0))
			{
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;

			}
		}
	}
}
void readFile(GRAPH &g,char path[20])
{
	initialGraph(g);
	FILE *f;
	f = fopen(path, "rt");
	if (f == NULL)
	{
		g.M = 0;
		return;
	}
	else
	{
		fscanf(f, "%d", &g.M);
		if (g.M < 0)
		{
			g.M = 0;
			fclose(f);
			return;
		}
		g.maTrix = new int *[g.M];
		for (int i = 0; i < g.M; i++)
		{
			g.maTrix[i] = new int[g.M];
		}
		for (int j = 0; j < g.M; j++)
		{
			for (int k = 0; k < g.M; k++)
			{
				fscanf(f, "%d", &g.maTrix[j][k]);
			}
		}
	}
	fclose(f);
}
void visit_DFS(GRAPH g,int i, int label,int* arrayLabel )
{
	arrayLabel[i] = label;
		for (int j = 0; j < g.M; j++)
		{
			if (g.maTrix[i][j] == 1 && arrayLabel[j] == 0 )
			{
				visit_DFS(g,j,label,arrayLabel);
			}
		}
}
int minArray(int *a, int n)
{

	int imin;
	int min = INT_MAX;
	for (int i = 1; i < n; i++)
	{
		if (a[i] < min && a[i] != 0 )
		{
			min = a[i];
			imin = i;
		}
	}
	return imin;
}
void write_DepthFirstSearch_ConnectedGraph(GRAPH g, char path[20])
{
	FILE *f;
	f = fopen(path, "wt");
	if (f == NULL)
	{
		printf("Error File");
		return;
	}
	else if (g.M == 0)
	{
		fprintf(f, "0\nIs Empty Graph");
	}
	else
	{
		if (checkConnectedVertex(g) == 1)
		{
			fprintf(f,"%d\n",g.M);
			for (int i = 0; i < g.M; i++)
			{
				fprintf(f, "%d\n", i);
			}
			fclose(f);
			return;
		}
		int i, j;
		int label = 0;
		int *arrayLabel = new int[g.M];
		// Gán nhãn cho tất cả các đỉnh. 
		for (i = 0; i < g.M; i++)
		{
			arrayLabel[i] = 0;
		}
		// Duyệt các đỉnh và thay đổi nhãn.
		for (j = 0; j < g.M; j++)
		{
			if (arrayLabel[j] == 0)
			{
				label += 1;
				visit_DFS(g, j, label, arrayLabel);
			}
		}
		int *arrayNumberConnected = countComponentsConnected(arrayLabel, g.M);
		int countNumberConnected = 0;// Số thành phần liên thông
		for (int i = 1; i <= g.M; i++)
		{
			if (arrayNumberConnected[i] != 0)
			{
				countNumberConnected++;
			}
		}
		fprintf(f, "%d\n", countNumberConnected);
		for (int i = 1; i < g.M; i++)
		{
			countNumberConnected++;
			int imin;
			if (arrayNumberConnected[i] != 0)
			{
				imin = minArray(arrayNumberConnected, g.M);
				for (int j = 0; j < g.M; j++)
				{
					if (imin == arrayLabel[j])
					{
						fprintf(f,"%d ", j);
					}
				}
				arrayNumberConnected[imin] = 0;
				i--;
				fprintf(f,"\n");
			}

		}

	}
	fclose(f);
}
void visit_BFS(GRAPH g, int *vertexLabel, int i, int label)
{
	queue <int> Q;
	Q.push(i);
	while (!(Q.empty()))
	{
		int k = Q.front();
		vertexLabel[k] = label;
		Q.pop();
		for (int j = 0; j < g.M; j++)
		{
			if (g.maTrix[k][j] == 1 && vertexLabel[j] == 0)
			{
				Q.push(j);
			}
		}
	}
}
void write_BreadthFirstSearch_ConnectedGraph(GRAPH g, char path[20])
{
	FILE *f;
	f = fopen(path, "wt");
	if (f == NULL)
	{
		g.M = 0;
		printf("Error file");
		return;
	}
	else if (g.M == 0)
	{
		fprintf(f, "0\nIs Empty Graph");
	}
	else
	{
		if (checkConnectedVertex(g) == 1)
		{
			fprintf(f, "%d\n", g.M);
			for (int i = 0; i < g.M; i++)
			{
				fprintf(f, "%d\n", i);
			}
			fclose(f);
			return;
		}
		int label = 0;
		int *vertexLabel = new int[g.M];
		for (int i = 0; i < g.M; i++)
		{
			vertexLabel[i] = 0;
		}
		for (int j = 0; j < g.M; j++)
		{
			if (vertexLabel[j] == 0)
			{
				label++;
				visit_BFS(g, vertexLabel, j, label);
			}
		}
		int *arrayNumberConnected = countComponentsConnected(vertexLabel, g.M);
		int countNumberConnected = 0;// Số thành phần liên thông
		for (int i = 1; i <= g.M; i++)
		{
			if (arrayNumberConnected[i] != 0)
			{
				countNumberConnected++;
			}
		}
		fprintf(f, "%d\n", countNumberConnected);
		for (int i = 1; i < g.M; i++)
		{
			countNumberConnected++;
			int imin;
			if (arrayNumberConnected[i] != 0)
			{
				imin = minArray(arrayNumberConnected, g.M);
				for (int j = 0; j < g.M; j++)
				{
					if (imin == vertexLabel[j])
					{
						fprintf(f, "%d ", j);
					}
				}
				arrayNumberConnected[imin] = 0;
				i--;
				fprintf(f, "\n");
			}
		}
	}
	fclose(f);
}
void main(int numberParameter, char* arrayParameters[])
{

	GRAPH g;
	std::string parameter(arrayParameters[1]);
	if (parameter == "d")
	{
		readFile(g, arrayParameters[2]);
		write_DepthFirstSearch_ConnectedGraph(g, arrayParameters[3]);
	}
	else if (parameter == "b")
	{
		readFile(g, arrayParameters[2]);
		write_BreadthFirstSearch_ConnectedGraph(g, arrayParameters[3]);
	}
	else
	{
		printf("Error File");
	}
	_getch();
}
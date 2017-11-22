#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void print_int_2darray(int ** arr, int num){
	printf("\n  ");
	for (size_t i = 0; i < num; i++)
	{
		if (i < 10)
		{
			printf("  %d ", i);
		}
		else
		{
			printf(" %d ", i);
		}
	}
	for (size_t i = 0; i < num; i++)
	{
		if (i < 10)
		{
			printf("\n %d", i);
		}
		else
		{
			printf("\n%d", i);
		}
		for (size_t j = 0; j < num; j++)
		{
			int x = arr[i][j];
			if (x == INFINITY || x == NULL)
			{
				printf("[  ]");
			}
			else if (x>9)
			{
				printf("[%d]", x);
			}
			else
			{
				printf("[ %d]", x);
			}
		}
	}
}

void print_1d_array(int **arr, int num){
	for (size_t i = 0; i < num; i++)
	{
		if (arr[i] == ENDOFPATH)
		{
			//print nothing
		}
		else
		{
			printf(" %d [ %d ]", i, arr[i]);
		}
	}
}

void destroy_edge_list(EdgeList *self) {
	EdgeNodePtr current = self->head;
	while (current != NULL) {
		EdgeNodePtr to_free = current;
		current = current->next;
		free(to_free);	//no idea why this isnt working >:(
	}
	self->head = NULL;
}

void destroy_int_2darray(int ** arr, int num){
	for (size_t i = 0; i < num; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
}

void destroy_graph(Graph * G){
	for (size_t i = 0; i < G->V; i++)
	{
		destroy_edge_list(&G->edges[i]);
	}
}

void FloydWarshal(Graph * G, int **dist, int **next){
	int num = G->V;

	for (size_t U = 0; U < num; U++)
	{
		EdgeNodePtr current = G->edges[U].head;
		int V; //for reaability using U and V
		while (current != NULL) {
			V = current->edge.to_vertex;
			dist[U][V] = current->edge.weight;
			next[U][V] = V;
			current = current->next;
		}
	}

	for (size_t K = 0; K < num; K++)
	{
		for (size_t i = 0; i < num; i++)
		{
			for (size_t j = 0; j < num; j++)
			{
				if (dist[i][j] >(dist[i][K] + dist[K][j])){
					dist[i][j] = (dist[i][K] + dist[K][j]);
					next[i][j] = next[i][K];
				}
			}
		}
	}
}

void path(int U, int V, int **next, int *pathUV){
	if (next[U][V] == ENDOFPATH)
	{
		pathUV[0] = ENDOFPATH;
		return;
	}
	int step = 0;
	while (U != V)
	{
		U = next[U][V];
		pathUV[step] = U;
		step++;
	}
	pathUV[step] = ENDOFPATH;
}

int is_inbetween(int *pathUV, int C){
	int i = 0;
	while (pathUV[i] != ENDOFPATH)
	{
		//if C is not the 1st or last Vertex and is in the path
		if (i != 0 && pathUV[i+1] != ENDOFPATH && pathUV[i] == C)
		{
			return 1;
		}
		i++;
	}
	return 0;
}

void centrality(int **next, int *cent, int num){
	int * pathUV = malloc(sizeof(*pathUV)*num);
	for (size_t	C = 0; C < num; C++)
	{
		for (size_t U = 0; U < num; U++)
		{
			for (size_t V = 0; V < num; V++)
			{
				//reset path result
				for (size_t i = 0; i < num; i++)
				{
					pathUV[i] = ENDOFPATH;
				}
				path(U, V, next, pathUV);//get shortest path
				//increment cent if C is in path from U to V
				cent[C] += is_inbetween(pathUV, C);
			}
		}
	}
	int highest = 0;
	int C = 0;
	for (size_t i = 0; i < num; i++)
	{
		if (cent[i] > highest)
		{
			C = i;
			highest = cent[i];
		}
	}
	printf("%d %d", C, highest);

	free(pathUV);
}
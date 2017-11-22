#include <stdio.h>
#include <stdlib.h>

#include "graph.h"


void destroy_edge_list(EdgeList *self) {
	EdgeNodePtr current = self->head;
	while (current != NULL) {
		EdgeNodePtr to_free = current;
		current = current->next;
		free(to_free);	//no idea why this isnt working >:(
	}
	self->head = NULL;
}

destroy_int_2darray(int ** arr, int v){
	for (size_t i = 0; i < v; i++)
	{
		for (size_t j = 0; j < v; j++)
		{
			free(&arr[i][j]);
			arr[i][j] = NULL;
		}
		free(&arr[i]);
		arr[i] = NULL;
	}
}

print_int_2darray(int ** arr, int v){
	printf("\n  ");
	for (size_t i = 0; i < v; i++)
	{
		if (i < 10)
		{
			printf("  %d  ",i);
		}
		else
		{
			printf(" %d  ", i);
		}
	}
	for (size_t i = 0; i < v; i++)
	{
		if (i < 10)
		{
			printf("\n %d", i);
		}
		else
		{
			printf("\n%d", i);
		}
		for (size_t j = 0; j < v; j++)
		{
			int x = arr[i][j];
			if (x == -1)
			{
				printf("[   ]");
			}
			else
			{
				printf("[ %d ]", x);
			}
		}
	}
}

void print_in_degrees(Graph * G){
	//Setup inDegrees storage
	int v = G->V;
	int * inDegrees = malloc(sizeof(int*)*v);
	for (size_t i = 0; i < v; i++)
	{
		inDegrees[i] = 0;
	}

	//GET INDEGEREEESS
	for (size_t i = 0; i < v; i++)
	{
		EdgeNodePtr current = G->edges[i].head;
		while (current != NULL)
		{
			int toV = current->edge.to_vertex;
			inDegrees[toV] ++;
			current = current->next;
		}
	}
	//Print results
	for (size_t i = 0; i < v; i++)
	{
		printf("\nIn degree of vertex %d is %d", i, inDegrees[i]);
	}
}

void get_dist(Graph * G, int ** dist){
	
}

int main() {
	int **dist; // VxV ints to store shortest path distances 
	int **next; // VxV ints to store shortest path data 
	int *cent;  // V ints to store the centrality score for each vertex 

	Graph G;
	int v = 0;
	int pair[2];
	int e = 0;

	//for the GRAPH

	//printf("How many verticies?\n");
	scanf("%d", &v);
	printf("%d\n", v);

	G.V = v; //store # of verticies in the graph
	G.edges = malloc(sizeof(EdgeList *)*v); //allocate mem for array of edge lists[v]

	//for each VERTEX
	for (size_t i = 0; i < v; i++)
	{
		//printf("How many Edges for Vertex %d?\n", i);
		scanf("%d", &e);
		printf("%d\n", e);
		int vi = i; //so we know what vertex this forloop is up to in deeper in.
		G.edges[vi].head = NULL;

		//for each EDGE
		for (size_t i = 0; i < e; i++)
		{
			//printf("Enter the edge pair %d in the format V,V\n", i);
			scanf("%d,%d", &pair[0], &pair[1]);
			pair[1] = 1; //input has no edges so just setting it to 1.
			printf("%d,%d ", pair[0], pair[1]);
			
			EdgeNodePtr newEdgePointer = malloc(sizeof(EdgeNodePtr));
			newEdgePointer->next = NULL;
			
			newEdgePointer->edge.to_vertex = pair[0];
			newEdgePointer->edge.weight = pair[1];

			//insert at front
			if (G.edges[vi].head == NULL)
			{
				//nothing yet just chuck it in
				G.edges[vi].head = newEdgePointer;
			}
			else
			{
				EdgeNodePtr temp = G.edges[vi].head;
				G.edges[vi].head = newEdgePointer;
				newEdgePointer->next = temp;
			}
		}
		if (e)
			printf("\n");
	}
	//GRAPH CREATED.


	//initialise distances
	dist = (int **)malloc(sizeof(int **)*v);
	for (size_t i = 0; i < v; i++)
	{
		dist[i] = (int *)malloc(sizeof(int *)*v);
		for (size_t j = 0; j < v; j++)
		{
			dist[i][j] = -1; //using -1 to represent infinity
		}
	}
	
	//initialise next
	next = (int **)malloc(sizeof(int **)*v);
	for (size_t i = 0; i < v; i++)
	{
		next[i] = (int *)malloc(sizeof(int *)*v);
		for (size_t j = 0; j < v; j++)
		{
			next[i][j] = NULL;
		}
	}


	//FloydWarshallWithPathReconstruction
	//for each  edge between 2 v's (u to v)
		//dist[u][v] = weight between them
		//next[u][v] = some fucking vertex...  wtf is next for.. IM just gonna iterate through v's in order for this fuck

	for (size_t i = 0; i < v; i++)
	{
		EdgeNodePtr current = G.edges[i].head;
		while (current != NULL) {
			dist[i][current->edge.to_vertex] = current->edge.weight;
			current = current->next;
		}
	}
	printf("\nCalculated distances between each Vertex:\n");
	print_int_2darray(dist, v);

	//for K from 1 to |V|... wtf is K!!!!!!! 

	//centrality ???

	/*
	
	centrality = number of shortest pasths that pass through the node..



	*/


	//FREEE MEMORY
	//destroy_int_2darray(dist, v);
	//destroy_int_2darray(next, v);
	for (size_t i = 0; i < v; i++)
	{
		//destroy_edge_list(&G.edges[i]);
		
	}

	printf("\nEnd\n");
	exit(0);
}
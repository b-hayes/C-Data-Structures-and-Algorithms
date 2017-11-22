#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define OFF 0;
#define ON 1;

int main() {
	const int DEBUG = ON; //show extra info?
	int **dist; // VxV ints to store shortest path distances 
	int **next; // VxV ints to store shortest path data 
	int *cent;  // V ints to store the centrality score for each vertex 
	Graph G;
	int num = 0;	//used for esier reference to Number of verticies in graph
	int pair[2];	//initially used for edge pair input with weights thats why its an array..
	int numEdges = 0;		//used for number of edges input
	
	//Input for the GRAPH

	//printf("How many verticies?\n");
	scanf("%d", &num);

	G.V = num;
	G.edges = malloc(sizeof(*G.edges)*num); //allocate mem for array of edge lists[num]

	//for each VERTEX
	for (size_t i = 0; i < num; i++)
	{
		scanf("%d", &numEdges);
		int current_vertex = i;
		G.edges[current_vertex].head = NULL;

		//for each EDGE
		for (size_t i = 0; i < numEdges; i++)
		{
			scanf("%d", &pair[0]);
			pair[1] = 1; //input stream has no edge wheights so just setting it to 1.

			EdgeNodePtr newEdgePointer = malloc(sizeof *newEdgePointer);
			newEdgePointer->next = NULL;

			newEdgePointer->edge.to_vertex = pair[0];
			newEdgePointer->edge.weight = pair[1];

			//insert new Edge at front of list
			if (G.edges[current_vertex].head == NULL)
			{
				//nothing yet just chuck it in
				G.edges[current_vertex].head = newEdgePointer;
			}
			else
			{
				EdgeNodePtr temp = G.edges[current_vertex].head;
				G.edges[current_vertex].head = newEdgePointer;
				newEdgePointer->next = temp;
			}
		}
	}
	//GRAPH CREATED.

	//initialise dist
	dist = malloc(sizeof(*dist)*num);
	for (size_t i = 0; i < num; i++)
	{
		dist[i] = malloc(sizeof(*dist[i])*num);
		for (size_t j = 0; j < num; j++)
		{
			dist[i][j] = INFINITY;
		}
	}

	//initialise next
	next = malloc(sizeof(*next)*num);
	for (size_t i = 0; i < num; i++)
	{
		next[i] = malloc(sizeof(*next[i])*num);
		for (size_t j = 0; j < num; j++)
		{
			next[i][j] = ENDOFPATH; //null was acting as 0
		}
	}

	//initialise cent
	cent = malloc(sizeof(*cent)*num);
	for (size_t i = 0; i < num; i++)
	{
		cent[i] = 0;
	}
	
	FloydWarshal(&G, dist, next);
	centrality(next, cent, num);


	if (DEBUG)
	{
		printf("Distances :\n");
		print_int_2darray(dist, num);
		printf("\n\nNexts :\n");
		print_int_2darray(next, num);
		printf("\n\nCentralities :\n");
		print_1d_array(cent, num);
		printf("\n");
	}

	

	//FREEE MEMORY
	free(cent);
	destroy_int_2darray(dist, num);
	destroy_int_2darray(next, num);
	destroy_graph(&G);

	printf("\nEnd\n");
	exit(0);
}
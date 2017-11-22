#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void destroy_edge_list(EdgeList *self) {
	EdgeNodePtr current = self->head;
	while (current != NULL) {
		EdgeNodePtr to_free = current;
		current = current->next;
		free(to_free);
	}
	self->head = NULL;
}

int main(){
	Graph G;
	int v = 0;
	int pair[2];
	int e = 0;
	
	//for the GRAPH

	//printf("How many verticies?\n");
	scanf("%d", &v);
	printf("%d\n", v);

	G.V = v; //store # of verticies in the graph
	G.edgeLists = malloc(sizeof(EdgeList)*v); //allocate mem for array of edge lists[v]
	
	//for each VERTEX
	for (size_t i = 0; i < v ; i++)
	{
		//printf("How many Edges for Vertex %d?\n", i);
		scanf("%d", &e);
		printf("%d\n", e);
		int vi = i; //so we know what vertex this forloop is up to in deeper in.
		G.edgeLists[vi].head = NULL;
		
		//for each EDGE
		for (size_t i = 0; i < e; i++)
		{
			//printf("Enter the edge pair %d in the format V,V\n", i);
			scanf("%d,%d", &pair[0], &pair[1]);
			printf("%d,%d ", pair[0], pair[1]);

			EdgeNodePtr newEdgePointer = malloc(sizeof(EdgeNodePtr));
			newEdgePointer->next = NULL;
			//Edge * newEdge = malloc(sizeof(Edge));
			//newEdge->to_vertex = pair[0];
			//newEdge->weight = pair[1];
			//newEdgePointer->edge = *newEdge;

			//dont actually need to malloc for this...
			newEdgePointer->edge.to_vertex = pair[0];
			newEdgePointer->edge.weight = pair[1];

			//insert at front
			if (G.edgeLists[vi].head == NULL)
			{
				//nothing yet just chuck it in
				G.edgeLists[vi].head = newEdgePointer;
			}
			else
			{
				EdgeNodePtr temp = G.edgeLists[vi].head;
				G.edgeLists[vi].head = newEdgePointer;
				newEdgePointer->next = temp;
			}
		}
		if (e)
			printf("\n");
	}
	//GRAPH CREATED.

	int * inDegrees = malloc(sizeof(int)*v);
	for (size_t i = 0; i < v; i++)
	{
		inDegrees[i] = 0;
	}

	//GET INDEGEREEESS
	for (size_t i = 0; i < v; i++)
	{
		EdgeNodePtr current = G.edgeLists[i].head;
		while (current!=NULL)
		{
			int toV = current->edge.to_vertex;
			inDegrees[toV] ++;
			current = current->next;
		}
	}

	for (size_t i = 0; i < v; i++)
	{
		printf("\nIn degree of vertex %d is %d", i, inDegrees[i]);
	}

	//FREEE MEMORY
	for (size_t i = 0; i < G.V; i++)
	{
		destroy_edge_list(&G.edgeLists[i]);
		
	}

	printf("\nEnd\n");
	exit(0);
}



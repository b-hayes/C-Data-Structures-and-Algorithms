#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "list.h"

void enqueue(Queue *self, int i){
	ListNodePtr temp = malloc(sizeof *temp);
	temp->data = i;
	temp->next = NULL;
	if (self->end == NULL){
		self->end = temp;
	}
	else
	{
		self->end->next = temp;
	}
	if (self->start == NULL){
		self->start = temp;
	}
}

int dequeue(Queue *self) {
	if (self->start == NULL){
		printf("ERROR: nothing in the queue but u trying to dequeue!\n");
		return -1;
	}
	int V = self->start->data;
	if (self->start == self->end){
		self->start = self->end = NULL;
	}
	else
	{
		self->start = self->start->next;
	}
	
	return V;
}


void bfs(Graph G){
	//print graph BFS
	Queue Q;
	Q.start = NULL;
	Q.end = NULL;

	int * discovered = malloc(sizeof(*discovered)*G.V);
	for (size_t i = 0; i < G.V; i++)
	{
		discovered[i] = 0;
	}
	
	//start at 0...
	enqueue(&Q, 0);
	printf("Vertex %d Discovered\n", 0);
	discovered[0] = 1;
	while (Q.start != NULL)
	{
		int current_vertex = dequeue(&Q);
		
		EdgeNodePtr E = G.edges[current_vertex].head;
		while (E != NULL)
		{
			int To = E->edge.to_vertex;
			if (discovered[To] == 0){
				enqueue(&Q, To);
				discovered[To] = 1;
				printf("Vertex %d Discovered\n", To);
			}
			E = E->next;
		}
		
	}
}



int main(){

	Graph G;
	G.V = 3;
	G.edges = malloc(sizeof(*G.edges)*G.V);
	//node 0 (a)
	EdgeNodePtr newEdgePointer = malloc(sizeof *newEdgePointer);
	newEdgePointer->next = NULL;
	newEdgePointer->edge.to_vertex = 1;
	newEdgePointer->edge.weight = 0;

	G.edges[0].head = newEdgePointer;

	newEdgePointer->next = malloc(sizeof *newEdgePointer);
	newEdgePointer = newEdgePointer->next;
	newEdgePointer->next = NULL;
	newEdgePointer->edge.to_vertex = 2;
	newEdgePointer->edge.weight = 0;

	

	//node 1 (b)
	newEdgePointer = malloc(sizeof *newEdgePointer);
	newEdgePointer->next = NULL;
	newEdgePointer->edge.to_vertex = 2;
	newEdgePointer->edge.weight = 0;

	G.edges[1].head = newEdgePointer;

	//node 2 (c)
	G.edges[2].head = NULL;

	//now we have a fucking graph
	bfs(G);
}

	
#include "list.h"

typedef struct edge{
	int to_vertex;
	int weight; // set to 1 for all edges  
} Edge;

typedef struct queue{
	ListNodePtr start;
	ListNodePtr end;
} Queue;

typedef struct edgeNode{
	Edge edge;
	struct edgeNode *next;
} *EdgeNodePtr;

typedef struct edgeList{
	EdgeNodePtr head;
} EdgeList;

typedef struct graph{
	int V;
	EdgeList *edges;
} Graph;

#define INFINITY 99999
#define ENDOFPATH -99999

void print_int_2darray(int ** arr, int num);
void destroy_int_2darray(int ** arr, int num);
void destroy_graph(Graph * G);
void FloydWarshal(Graph * G, int **dist, int **next);
void centrality(int **next, int **cent, int num);
void print_1d_array(int **arr, int num);
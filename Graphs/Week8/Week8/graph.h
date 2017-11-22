typedef struct edge{ //edge info storage
	int to_vertex;
	int weight;
} Edge;

typedef struct edgeNode{
	Edge edge; //the actual edge informaiton storage (DONT NEED TO MALOC FOR THIS ITS A STRUCT NOT A POINTER)
	struct edgeNode *next;//to next edge storage box
} *EdgeNodePtr;

typedef struct edgeList{
	EdgeNodePtr head; //link first EdgeStorageBox for edgelists[vertex]
} EdgeList;

typedef struct graph{
	int V;
	EdgeList *edgeLists; //array of Edgelists..
} Graph;
#include "graph.h"
#include "list.h"
#include <stdlib.h>
#include <assert.h>

struct s_vertex {
	void* data;

	list vertices;
};
typedef struct s_vertex* vertex;

struct s_graph {
	unsigned nbVertex;
	unsigned nbEdge;

	list collection;
};

graph graph_create() {
	graph born =malloc(sizeof(struct s_graph));

	born->nbVertex =0;
	born->nbEdge =0;

	born->collection =list_create();
	
	return born;
}

void graph_destroy(graph* g) {
	list l =(*g)->collection;
	while (! list_empty(l)) {
		vertex v =list_back(l);
		list_destroy(&v->vertices);
		free(v);
		list_popBack(l);
	}
	list_destroy(&(*g)->collection);
	free(*g);
}

void graph_insertVertex(graph g ,void* data) {
	/* assert(! graph_findVertex(g ,data)); */
	vertex v =malloc(sizeof(struct s_vertex));
	v->data =data;
	v->vertices =list_create();

	list_pushBack(g->collection ,v);
	g->nbVertex++;
}



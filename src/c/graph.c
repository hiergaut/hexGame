#include "graph.h"
#include "list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "sdl.h"


struct s_vertex {
	const void* data;

	list vertices;
};
typedef struct s_vertex* vertex;

struct s_graph {
	unsigned nbVertex;
	unsigned nbEdge;

	list collection;
};

vertex graph_findVertex(list l ,const void* data) {
	list_it it =list_it_create(l);
	while (! list_it_end(it)) {
		vertex v =list_it_get(it);
		if (v->data ==data)
			return v;

		list_it_next(it);
	}
	list_it_destroy(&it);

	return NULL;
}

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

void graph_insertVertex(graph g ,const void* data) {
	assert(! graph_findVertex(g->collection ,data));

	vertex v =malloc(sizeof(struct s_vertex));
	v->data =data;
	v->vertices =list_create();

	list_pushBack(g->collection ,v);
	g->nbVertex++;
}

void graph_insertEdge(graph g ,const void* data ,const void* data2) {
	vertex v =graph_findVertex(g->collection ,data);
	vertex v2 =graph_findVertex(g->collection ,data2);

	assert(v);
	assert(v2);

	assert(! graph_findVertex(v->vertices ,v2));
	assert(! graph_findVertex(v2->vertices ,v));

	list_pushBack(v->vertices ,v2);
	list_pushBack(v2->vertices ,v);
}

void graph_print(graph g) {
	(void)g;
	/* list l =g->collection; */
	/* vertex v; */
	/* printf("je vais faire un fucking truc avec la SDL pour voir les liens et tout entre les sommets etc\n"); */
	/* sdl s =sdl_create(); */
    /*  */
    /*  */
	/* v =list_front(l); */
	/* sdl_newObject(s ,v->data); */
	/* sdl_newObject(s ,v); */
	/* sdl_newObject(s ,s); */
	/* sdl_link(s ,v ,s); */
    /*  */
	/* sdl_pause(); */
	/* sdl_destroy(&s); */
	/* vertex v; */
	/* sdl_addRec(s ,v->data); */
	/* sdl_addRec(s ,v2->data); */
	/* sdl_link(s ,v->data ,v2->data); */
	/* sdl_display(s); */
	/* sdl_destroy(s); */
}

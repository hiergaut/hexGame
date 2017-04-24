#include "graph.h"
#include "list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


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

vertex findVertex(list l, const void* data) {
    list_it it =list_it_create(l);
    while (! list_it_end(it)) {
	vertex v =list_it_get(it);
	if (v->data ==data) {
	    list_it_destroy(&it);
	    return v;
	}

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
	list_destroy(&(v->vertices));
	free(v);
	list_popBack(l);
    }
    list_destroy(&(*g)->collection);
    free(*g);
}

void graph_insertVertex(graph g, const void* data) {
    assert(! findVertex(g->collection, data));

    vertex v =malloc(sizeof(struct s_vertex));
    v->data =data;
    v->vertices =list_create();

    list_pushBack(g->collection, v);
    g->nbVertex++;
}


void graph_insertEdge(graph g, const void* data, const void* data2) {
    vertex v =findVertex(g->collection, data);
    vertex v2 =findVertex(g->collection, data2);

    assert(v);
    assert(v2);

    assert(! findVertex(v->vertices, v2));
    assert(! findVertex(v2->vertices, v));

    /* printf("link %p <-> %p\n" ,(void*)v ,(void*)v2); */

    list_pushBack(v->vertices, v2);
    list_pushBack(v2->vertices, v);
}

void printColor(const void* ptr) {
    int color =*(const int*)ptr %15;
    if (color ==0)
	color =0;
    else if (color ==1)
	color =7;
    else if (color <8)
	color =31 +color -2;
    /* else if (color <15) */
    else
	color =41 +color -8;
    /* else { */
	/* printf("\x1B[%d;3m%p\x1B[0m ", color -15, ptr); */
	/* return; */
    /* } */

    printf("\x1B[%dm%p\x1B[0m ", color, ptr);
}

void printVertex(void* v) {
    printColor((vertex)v);
}


void graph_print(graph g) {
    list_it it =list_it_create(g->collection);
    while (! list_it_end(it)) {
	vertex v =list_it_get(it);
	printColor(v);
	printf("%d " ,list_getSize(v->vertices));
	list_map(v->vertices, printVertex);
	printf("\n");

	list_it_next(it);
    }
    list_it_destroy(&it);


    /* list l =g->collection; */
    /* vertex v; */
    /* printf("je vais faire un fucking truc avec la SDL pour voir les liens et tout entre les sommets etc\n"); */
    /* sdl s =sdl_create(); */
    /*  */
    /*  */
    /* v =list_front(l); */
    /* sdl_newObject(s, v->data); */
    /* sdl_newObject(s, v); */
    /* sdl_newObject(s, s); */
    /* sdl_link(s, v, s); */
    /*  */
    /* sdl_pause(); */
    /* sdl_destroy(&s); */
    /* vertex v; */
    /* sdl_addRec(s, v->data); */
    /* sdl_addRec(s, v2->data); */
    /* sdl_link(s, v->data, v2->data); */
    /* sdl_display(s); */
    /* sdl_destroy(s); */
}

void graph_testBench() {
    graph g =graph_create();

    int tab[50];
    for (int i =0; i <20 ;i++) {
	tab[i] =rand() %100;
	graph_insertVertex(g, &tab[i]);
    }

    graph_insertEdge(g, &tab[0], &tab[1]);
    graph_insertEdge(g, &tab[0], &tab[3]);
    graph_insertEdge(g, &tab[2], &tab[3]);
    graph_insertEdge(g, &tab[5], &tab[3]);
    
    graph_print(g);

    graph_destroy(&g);
}

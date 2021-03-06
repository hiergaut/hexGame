#ifndef __GRAPH__
#define __GRAPH__

#include "list.h"

typedef struct s_graph* graph;
typedef struct s_vertex* vertex;

vertex graph_findVertex(list l, const void* data);
graph graph_create();
void graph_destroy(graph* g);
void graph_insertVertex(graph g, void* data);
void graph_delVertex(graph g, void* data);
void graph_unlink(vertex v, vertex v2);
void graph_insertEdge(graph g, const void* data, const void* data2);
void graph_print(graph g);
void graph_testBench();

list graph_getCollection(graph g);
void* graph_getData(vertex v);
list graph_getVertices(vertex v);
int graph_onlyVertex(vertex v);

int graph_sameGroup(graph g, const void* data, const void* data2);
int graph_neighbourVertex(graph g, const void* data, const void* data2);
int graph_smallerWay(graph g, graph wall, void* data, void* data2);
void* graph_middleWay(graph g, graph wall, graph all, void* data, void* data2, int ith);
graph graph_cat(graph g, graph g2);
#endif

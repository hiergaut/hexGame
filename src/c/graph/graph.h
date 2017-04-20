#ifndef __GRAPH__
#define __GRAPH__

typedef struct s_graph* graph;

graph graph_create();
void graph_destroy(graph* g);
void graph_insertVertex(graph g, const void* data);
void graph_insertEdge(graph g, const void* data, const void* data2);
void graph_print(graph g);
void graph_testBench();

#endif

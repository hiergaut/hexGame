#ifndef __GRAPH__
#define __GRAPH__

typedef struct s_graph* graph;

graph graph_create();
void graph_destroy(graph* g);
void graph_insertVertex(graph g ,void* data);

#endif

#include "graph.h"
#include <stdlib.h>

int main() {
    /* graph_testBench(); */
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


    return 0;
}

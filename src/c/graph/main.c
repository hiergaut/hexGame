#include "graph.h"
#include <stdlib.h>

int main() {
    graph g =graph_create();

    int tab[50];
    for (int i =0; i <20 ;i++) {
	tab[i] =rand() %100;
	graph_insertVertex(g, &tab[i]);
    }

    graph_print(g);

    graph_insertEdge(g, &tab[0], &tab[1]);
    

    graph_destroy(&g);
    return 0;
}

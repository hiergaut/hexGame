#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    /* graph_testBench(); */
    graph g =graph_create();

    int tab[50];
    for (int i =0; i <20 ;i++) {
        /* tab[i] =rand() %100; */
        tab[i] =i;
        graph_insertVertex(g, &tab[i]);
    }

    graph_insertEdge(g, &tab[0], &tab[1]);
    graph_insertEdge(g, &tab[1], &tab[2]);
    graph_insertEdge(g, &tab[2], &tab[3]);
    graph_insertEdge(g, &tab[3], &tab[4]);
    graph_insertEdge(g, &tab[4], &tab[5]);
    graph_insertEdge(g, &tab[5], &tab[6]);

    /* graph_insertEdge(g, &tab[0], &tab[4]); */

    graph_print(g);


    graph g2 =graph_create();
    graph_insertVertex(g2, &tab[7]);
    graph_insertEdge(g, &tab[7], &tab[3]);
    printf("0->6 =%d\n", graph_smallerWay(g, g2, &tab[3], &tab[5]));

    /* printf("%p\n", graph_middleWay(g, g2, &tab[0], &tab[1], 1)); */

    graph_destroy(&g2);

    graph_destroy(&g);


    return 0;
}

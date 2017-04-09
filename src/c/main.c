#include "plateau.h"
#include <stdio.h>
#include "graph.h"
/* #include "SDL/SDL.h" */

int main() {
	plateau p =plateau_create(5 ,5);
	graph g =graph_create();


	int a =5;
	plateau_insert(p ,0 ,0 ,&a);
	graph_insertVertex(g ,&a);

	plateau_print(p);
	graph_print(g);


	plateau_destroy(&p);
	graph_destroy(&g);


	return 0;
}

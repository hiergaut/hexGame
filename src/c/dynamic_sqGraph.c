#include "sqGraph.h"
#include <math.h>
#include <malloc.h>


typedef struct s_vertex* Vertex;
struct s_vertex {
	void* element;

	Vertex* edge;
};


struct s_sqGraph {
	Vertex** matrice;

	Vertex* reserve;
	unsigned side;
};

sqGraph sqGraph_create(unsigned side) {
	sqGraph born =malloc(sizeof(struct s_sqGraph));

	born->matrice =malloc(sizeof(struct s_vertex) *pow(side ,2));

}

#include "sqGraph.h"
#include <math.h>
#include <malloc.h>
#include "list.h"


typedef struct s_vertex* vertex;
struct s_vertex {
    void* element;

    list edges;
};


struct s_sqGraph {
    vertex** matrice;

    struct s_vertex left;
    struct s_vertex down;
    struct s_vertex right;
    struct s_vertex up;

    unsigned line;
    unsigned column;
};

void sqGraph_link(vertex a, vertex b) {
    list_pushBack(a->edges, b);
    list_pushBack(b->edges, a);
}

sqGraph sqGraph_create(unsigned line, unsigned column) {
    sqGraph born =malloc(sizeof(struct s_sqGraph));

    born->matrice =malloc(sizeof(struct s_vertex*) *line);
    for (unsigned i =0 ;i <line ;i++) {
	born->matrice[i] =malloc(sizeof(struct s_vertex) *column);

	for (unsigned j =0 ;j <column ;j++) {
	    vertex new =born->matrice[i][j] =malloc(sizeof(struct s_vertex));

	    new->edges =list_create();

	    if (i ==0)
		sqGraph_link(new, &born->up);
	    else
		sqGraph_link(new, born->matrice[i -1][j]);

	    if (i ==(line -1))
		sqGraph_link(new, &born->down);

	    if (j ==0)
		sqGraph_link(new, &born->left);
	    else
		sqGraph_link(new, born->matrice[i][j -1]);

	    if (j ==(column -1))
		sqGraph_link(new, &born->right);

	    if (j !=(column -1) && i !=0)
		sqGraph_link(new, born->matrice[i -1][j +1]);
	}
    }

    born->line =line;
    born->column =column;
    return born;
}

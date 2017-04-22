#include "interface.h"
#include "plateau.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

struct s_interface {
    plateau p;

    // graph of plateau
    graph g;

    // black and white pawn group
    graph black;
    graph white;
};


interface interface_create(unsigned side) {
    interface i =malloc(sizeof(struct s_interface));

    i->p =plateau_create(side, side);
    i->g =graph_create();

    i->black =graph_create();
    i->white =graph_create();

    return i;
}

void interface_destroy(interface* i) {
    plateau_destroy(&(*i)->p);
    graph_destroy(&(*i)->g);

    graph_destroy(&(*i)->black);
    graph_destroy(&(*i)->white);

    free(*i);
    *i =NULL;
}



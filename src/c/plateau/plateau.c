#include "plateau.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct s_plateau {
    unsigned line;
    unsigned column;

    unsigned density;

    void*** square;
};


plateau plateau_create(unsigned line, unsigned column) {
    plateau born =malloc(sizeof(struct s_plateau));

    born->line =line;
    born->column =column;
    born->density =0;

    born->square =malloc(sizeof(void**) *line);
    for (unsigned i =0 ;i <line ;i++) {

	born->square[i] =malloc(sizeof(void*) *column);
	for (unsigned j =0 ;j <column ;j++) {

	    born->square[i][j] =NULL;
	}
    }

    return born;
}

void plateau_destroy(plateau* p) {
    for (unsigned i =0 ;i <(*p)->line ;i++) {
	free((*p)->square[i]);
    }
    free((*p)->square);

    free(*p);
    *p =NULL;
}

void printColor2(const void* ptr) {
    int color;
    if (ptr ==NULL)
	color =0;
    else
	color =*(const int*)ptr %15;

    if (color ==0)
	color =0;
    else if (color ==1)
	color =7;
    else if (color <8)
	color =31 +color -2;
    /* else if (color <15) */
    else
	color =41 +color -8;
    /* else { */
	/* printf("\x1B[%d;3m%p\x1B[0m ", color -15, ptr); */
	/* return; */
    /* } */

    printf("\x1B[%dm%9p\x1B[0m ", color, ptr);
}

void plateau_print(plateau p) {
    for (unsigned i =0 ;i <p->line ;i++) {
	for (unsigned j =0 ;j <p->column ;j++) {
	    /* printf("%15p", p->square[i][j]); */
	    printColor2(&p->square[i][j]);
	    printColor2(p->square[i][j]);
	    printf("  ");
	}
	printf("\n");
    }
    printf("\n");
}

void plateau_insert(plateau p, unsigned line, unsigned column, void* square) {
    assert(line <p->line);
    assert(column <p->column);
    assert(!(p->square[line][column] && square));

    if (p->square[line][column]) {
        if (square ==NULL)
            p->density--;
    else
        if (square !=NULL)
            p->density++;
    }
    p->square[line][column] =square;
}

void* plateau_get(plateau p, unsigned line, unsigned column) {
    assert(line <p->line);
    return p->square[line][column];
}

void* plateau_getPtr(plateau p, unsigned line, unsigned column) {
    assert(line <p->line);
    return &p->square[line][column];
}

int plateau_getNbLine(plateau p) {
    return (int)p->line;
}

int plateau_getNbColumn(plateau p) {
    return (int)p->column;
}
/* void plateau_map(plateau p, void (*process)(void* data)) { */
/* 	for (unsigned i =0 ;i <p->line ;i++) { */
/* 		for (unsigned j =0 ;j <p->column ;j++) { */
/* 			process(p->square[i][j]); */
/* 		} */
/* 	} */
/* } */
/*  */
plateau plateau_copy(plateau p) {
    plateau copy =plateau_create(p->line, p->column);

    for (unsigned l =0; l <copy->line; l++) {
        for (unsigned c =0; c <copy->column; c++) {
            plateau_insert(copy, l, c, plateau_get(p, l, c));
        }
    }
    return copy;
}

int plateau_getDensity(plateau p) {
    return (int)p->density;
}

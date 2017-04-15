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

plateau plateau_create(unsigned line ,unsigned column) {
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

void plateau_print(plateau p) {
	for (unsigned i =0 ;i <p->line ;i++) {
		for (unsigned j =0 ;j <p->column ;j++) {
			printf("%15p" ,p->square[i][j]);
		}
		printf("\n");
	}
}

void plateau_insert(plateau p ,unsigned line ,unsigned column ,void* square) {
	assert(line <p->line);
	assert(column <p->column);
	assert(! p->square[line][column]);

	p->square[line][column] =square;
	p->density++;
}

void* plateau_get(plateau p ,unsigned line ,unsigned column) {
	return p->square[line][column];
}
/* void plateau_map(plateau p ,void (*process)(void* data)) { */
/* 	for (unsigned i =0 ;i <p->line ;i++) { */
/* 		for (unsigned j =0 ;j <p->column ;j++) { */
/* 			process(p->square[i][j]); */
/* 		} */
/* 	} */
/* } */
/*  */

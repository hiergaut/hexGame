#include "interface.h"
#include "plateau.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "sdl.h"
#include <assert.h>
/* #include "ihm.h" */

void interface_drawPlateau(plateau p);

struct s_interface {
    unsigned size;
    plateau p;

    // graph of plateau
    graph g;
    int whiteSide1;
    int whiteSide2;
    int blackSide1;
    int blackSide2;

    int whitePawn;
    int blackPawn;

    // black and white pawn group
    graph blackGroup;
    graph whiteGroup;

    SDL_Surface* surface_plateau;
    SDL_Surface* surface_graph;
};


interface interface_create(unsigned side) {
    interface i =malloc(sizeof(struct s_interface));

    i->size =side;
    i->p =plateau_create(side, side);

    i->g =graph_create();
    graph_insertVertex(i->g, &i->whiteSide1);
    graph_insertVertex(i->g, &i->whiteSide2);
    graph_insertVertex(i->g, &i->blackSide1);
    graph_insertVertex(i->g, &i->blackSide2);
    for (unsigned l =0; l <side; l++) {
	for (unsigned c =0; c <side; c++) {
	    graph_insertVertex(i->g, plateau_getPtr(i->p, l, c));

	    if (l ==0)
		graph_insertEdge(i->g, &i->blackSide1, plateau_getPtr(i->p, l, c));
	    else
		graph_insertEdge(i->g, plateau_getPtr(i->p, l -1, c), plateau_getPtr(i->p, l, c));
	    
	    if (c ==0)
		graph_insertEdge(i->g, &i->whiteSide1, plateau_getPtr(i->p, l, c));
	    else
		graph_insertEdge(i->g, plateau_getPtr(i->p, l, c -1), plateau_getPtr(i->p, l, c));

	    if (l ==side -1)
		graph_insertEdge(i->g, &i->blackSide2, plateau_getPtr(i->p, l, c));

	    if (c ==side -1)
		graph_insertEdge(i->g, &i->whiteSide2, plateau_getPtr(i->p, l, c));

	    if (l !=0 && c !=side -1)
		graph_insertEdge(i->g, plateau_getPtr(i->p, l, c), plateau_getPtr(i->p, l -1, c +1));
	}
    }

    i->blackGroup =graph_create();
    graph_insertVertex(i->blackGroup, &i->blackSide1);
    graph_insertVertex(i->blackGroup, &i->blackSide2);

    i->whiteGroup =graph_create();
    graph_insertVertex(i->whiteGroup, &i->whiteSide1);
    graph_insertVertex(i->whiteGroup, &i->whiteSide2);

    sdl_create(800, 600, "HegGame");
    int wBox =350;
    int hBox =250;
    int margin =25;
    i->surface_plateau =sdl_newSurface(wBox, hBox, margin, margin, "plateau");
    interface_displayPlateau(i);

    i->surface_graph =sdl_newSurface(wBox, hBox, 2 *margin +wBox, margin, "graph");
    interface_displayGraphGame(i);

    /* interface_drawPlateau(i->s, i->p); */

    return i;
}

void interface_destroy(interface* i) {
    plateau_destroy(&(*i)->p);
    graph_destroy(&(*i)->g);

    graph_destroy(&(*i)->blackGroup);
    graph_destroy(&(*i)->whiteGroup);

    SDL_FreeSurface((*i)->surface_plateau);
    sdl_quit();

    free(*i);
    *i =NULL;
}

bool interface_legalityPawn(unsigned line, unsigned column) {
    (void)line;
    (void)column;
    return true;
}

void interface_placePawn(interface i, int colorPawn, unsigned line, unsigned column) {
    switch (colorPawn) {
	case interface_BLACK_PAWN:
	    plateau_insert(i->p, line, column, &i->blackPawn); 
	    break;

	case interface_WHITE_PAWN:
	    plateau_insert(i->p, line, column, &i->whitePawn);
	    break;

	default:
	    break;
    }

    interface_majScreen(i);

    (void)colorPawn;
    (void)line;
    (void)column;
}

int interface_getPawn(unsigned line, unsigned column) {
    (void)line;
    (void)column;
    return 1;
}

int interface_winner() {
    return 1;
}

int interface_saveGame() {
    return 0;
}

void interface_restoreGame(int idGame) {
    (void)idGame;
}

void interface_displayHistory() {
    printf("History of previous game\n");
}

void interface_undo() {
}

void interface_displayGraphGame(interface i) {
    graph_print(i->g);
}

void interface_displayPlateau(interface i) {
    plateau_print(i->p);
    int line =plateau_getNbLine(i->p);
    int column =plateau_getNbColumn(i->p);
    assert(line ==column);

    int marginX;
    int caseSize;
    int marginY;
    SDL_Surface* area =i->surface_plateau;
    if (area->w >area->h) {
	caseSize =area->h /line;
	marginX =(area->w -area->h) /2;
	marginY =(area->h -caseSize *line) /2;
    }
    else {
	caseSize =area->w /line;
	marginX =(area->w -caseSize *line) /2;
	marginY =(area->h -area->w) /2;
    }

    int x;
    int y;
    void* data;
    for (int l =0; l <line; l++) {
	for (int c =0; c <column; c++) {
	    x =marginX +c *caseSize;
	    y =marginY +l *caseSize;
	    data =plateau_getPtr(i->p, (unsigned)l, (unsigned)c);
	    (void)data;
	    sdl_square(area, x, y, caseSize, SDL_BLACK);
	    sdl_floodfill(area, x +1, y +1, sdl_uniqColorData(data), SDL_BLACK);
	    sdl_circle(area, x +caseSize /2, y +caseSize /2, caseSize /3, SDL_WHITE);

	    data =plateau_get(i->p, (unsigned)l, (unsigned)c);
	    sdl_floodfill(area, x +caseSize /2, y +caseSize /2, sdl_uniqColorData(data), SDL_WHITE);
	}
    }
    SDL_BlitSurface(area, NULL, screen, &area->clip_rect);
    SDL_Flip(screen);
}

void interface_displayGroup(interface i, int color) {
    if (color ==1)
	graph_print(i->blackGroup);
    else
	graph_print(i->whiteGroup);
}

void interface_majScreen(interface i) {
    interface_displayPlateau(i);
}

/* void interface_drawPlateau(plateau p) { */
/*  */
/* } */

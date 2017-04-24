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
    SDL_Surface* surface_blackGroup;
    SDL_Surface* surface_whiteGroup;
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

    int width =800;
    int height =600;
    int dec =10;
    sdl_create(width, height, "HegGame");
    int margin =30;
    int wBox =(width -3 *margin) /2;
    int hBox =(height -3 *margin) /2;
    i->surface_plateau =sdl_newSurface(wBox, hBox, margin, margin +dec, "plateau");
    interface_displayPlateau(i);

    i->surface_graph =sdl_newSurface(wBox, hBox, 2 *margin +wBox, margin +dec, "graph");
    interface_displayGraph(i, i->g, i->surface_graph);

    i->surface_blackGroup =sdl_newSurface(wBox, hBox, margin, 2 *margin +hBox +dec, "blackGroup");
    interface_displayGraph(i, i->blackGroup, i->surface_blackGroup);

    i->surface_whiteGroup =sdl_newSurface(wBox, hBox, 2 *margin +wBox, 2 *margin +hBox +dec, "whiteGroup");
    interface_displayGraph(i, i->whiteGroup, i->surface_whiteGroup);
    /* interface_drawPlateau(i->s, i->p); */

    return i;
}

void interface_destroy(interface* i) {
    plateau_destroy(&(*i)->p);
    graph_destroy(&(*i)->g);

    graph_destroy(&(*i)->blackGroup);
    graph_destroy(&(*i)->whiteGroup);

    SDL_FreeSurface((*i)->surface_plateau);
    SDL_FreeSurface((*i)->surface_graph);
    SDL_FreeSurface((*i)->surface_blackGroup);
    SDL_FreeSurface((*i)->surface_whiteGroup);
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
    void* data =plateau_getPtr(i->p, line, column);
    assert(data);
    graph group;
    switch (colorPawn) {
	case interface_BLACK_PAWN:
	    plateau_insert(i->p, line, column, &i->blackPawn); 
	    group =i->blackGroup;
	    /* graph_insertVertex(i->blackGroup, data); */
	    break;

	case interface_WHITE_PAWN:
	    plateau_insert(i->p, line, column, &i->whitePawn);
	    group =i->whiteGroup;
	    /* graph_insertVertex(i->whiteGroup, data); */
	    break;

	default:
	    break;
    }

    graph_insertVertex(group, data);

    vertex vGraph =graph_findVertex(graph_getCollection(i->g), data);
    assert(vGraph);

    vertex vGroup =graph_findVertex(graph_getCollection(group), data);
    assert(vGroup);

    list_it it_vertices =list_it_create(graph_getVertices(vGraph));
    while (! list_it_end(it_vertices)) {
	vertex vGraphVertices =list_it_get(it_vertices);

	void* caseCur =graph_getData(vGraphVertices);

	if (graph_findVertex(graph_getCollection(group), caseCur)) {
	    graph_insertEdge(group, data, caseCur);
	}

	list_it_next(it_vertices);
    }
    list_it_destroy(&it_vertices);

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

SDL_Rect interface_graphCase(interface i, SDL_Surface* area, void* data, int marginX, int marginY, int caseSize, int line, int column) {
    SDL_Rect pos;

    if (data ==&i->whiteSide1) {
	/* sdl_squareFill(area, 0, area->h /2 -caseSize /2, caseSize, SDL_BLACK, sdl_uniqColorData(data)); */
	pos.x =(short)(0);
	pos.y =(short)(area->h /2 -caseSize /2);
	return pos;
    }
    if (data ==&i->whiteSide2) {
	/* sdl_squareFill(area, area->w -caseSize, area->h /2 -caseSize /2, caseSize, SDL_BLACK, sdl_uniqColorData(data)); */
	pos.x =(short)((area->w -1) -caseSize);
	pos.y =(short)(area->h /2 -caseSize /2);
	return pos;
    }
    if (data ==&i->blackSide1) {
	pos.x =(short)(area->w /2 -caseSize /2);
	pos.y =(short)(0);
	/* sdl_squareFill(area, area->w /2 -caseSize /2, 0, caseSize, SDL_BLACK, sdl_uniqColorData(data)); */
	return pos;
    }
    if (data ==&i->blackSide2) {
	/* sdl_squareFill(area, area->w /2 -caseSize /2, area->h -caseSize, caseSize, SDL_BLACK, sdl_uniqColorData(data)); */
	pos.x =(short)(area->w /2 -caseSize /2);
	pos.y =(short)((area->h -1) -caseSize);
	return pos;
    }

    /* int x; */
    /* int y; */
    for (int l =0; l <line; l++) {
	for (int c =0; c <column; c++) {
	    if (plateau_getPtr(i->p, (unsigned)l, (unsigned)c) ==data) {
		pos.x =(short)(marginX +c *(2 *caseSize) +l *caseSize);
		pos.y =(short)(marginY +l *(2 *caseSize));
		/* sdl_squareFill(area, x, y, caseSize, SDL_BLACK, sdl_uniqColorData(data)); */
                /*  */
		/* SDL_BlitSurface(area, NULL, screen, &area->clip_rect); */
		/* SDL_Flip(screen); */
		return pos;
	    }
	}
    }
    assert(0);
}

void interface_displayGraph(interface i, graph g, SDL_Surface* area) {
    /* graph_print(i->g); */
    sdl_clean(area);
    graph_print(g);

    int line =plateau_getNbLine(i->p);
    int column =plateau_getNbColumn(i->p);
    assert(line ==column);

    int caseSize;
    int marginX;
    int marginY;
    int boxW;

    /* SDL_Surface* area =i->surface_graph; */
    if (area->w >area->h) {
	caseSize =area->h /(3 +2 *line);
	boxW =caseSize *(2 *column -1 +line);
	marginX =(area->w -boxW) /2;
	marginY =2 *caseSize;
    }
    else {
	caseSize =area->w /(line *2);
	marginX =(area->w -caseSize *line) /2;
	marginY =(area->h -area->w) /2;
    }

    /* list collection =graph_getCollection(i->g); */
    /* list_it it_collection =list_it_create(graph_getCollection(i->g)); */
    list_it it_collection =list_it_create(graph_getCollection(g));
    void* data;
    SDL_Rect pos, pos2;
    while (! list_it_end(it_collection)) {
	vertex v =list_it_get(it_collection);

	data =graph_getData(v);
	pos =interface_graphCase(i, area, data, marginX, marginY, caseSize, line, column);

	list_it it_vertices =list_it_create(graph_getVertices(v));
	while (! list_it_end(it_vertices)) {
	    vertex v2 =list_it_get(it_vertices);
	    data =graph_getData(v2);

	    pos2 =interface_graphCase(i, area, data, marginX, marginY, caseSize, line, column);
	    sdl_lineSimple(area, pos.x +caseSize /2, pos.y +caseSize /2, pos2.x +caseSize /2, pos2.y +caseSize /2, SDL_RED);

	    list_it_next(it_vertices);
	}
	list_it_destroy(&it_vertices);


	list_it_next(it_collection);
    }
    
    list_it_restart(it_collection);
    while (! list_it_end(it_collection)) {
	vertex v =list_it_get(it_collection);

	data =graph_getData(v);
	pos =interface_graphCase(i, area, data, marginX, marginY, caseSize, line, column);

	sdl_squareFill(area, pos.x, pos.y, caseSize, SDL_BLACK, sdl_uniqColorData(data));

	list_it_next(it_collection);
    }

    list_it_destroy(&it_collection);

    SDL_BlitSurface(area, NULL, screen, &area->clip_rect);
    SDL_Flip(screen);
}

void interface_displayPlateau(interface i) {
    sdl_clean(i->surface_plateau);

    plateau_print(i->p);
    int line =plateau_getNbLine(i->p);
    int column =plateau_getNbColumn(i->p);
    assert(line ==column);

    int marginX;
    int caseSize;
    int marginY;
    SDL_Surface* area =i->surface_plateau;
    if (area->w >area->h) {
	caseSize =(area->h -1) /line;
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
    if (color ==interface_BLACK_PAWN)
	graph_print(i->blackGroup);
    else
	graph_print(i->whiteGroup);
}

void interface_majScreen(interface i) {
    /* sdl_clean(i->surface_graph); */
    /* sdl_pause(); */
    interface_displayPlateau(i);
    interface_displayGraph(i, i->g, i->surface_graph);
    interface_displayGraph(i, i->blackGroup, i->surface_blackGroup);
    interface_displayGraph(i, i->whiteGroup, i->surface_whiteGroup);

    /* interface_drawPlateau(i->s, i->p); */

}

/* void interface_drawPlateau(plateau p) { */
/*  */
/* } */

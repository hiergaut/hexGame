#include "interface.h"
#include "plateau.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "sdl.h"
#include <assert.h>
#include <math.h>
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
    SDL_Surface* surface_ihm;

    graph reduceGraph;
    SDL_Surface* surface_reduceGraph;

    list casePlayed;
    list caseRedo;
    list caseRedoColor;
    int redoActive;
};

void interface_buildGraphPlateau(interface i, graph g) {
    graph_insertVertex(g, &i->whiteSide1);
    graph_insertVertex(g, &i->whiteSide2);
    graph_insertVertex(g, &i->blackSide1);
    graph_insertVertex(g, &i->blackSide2);
    unsigned side =i->size;
    for (unsigned l =0; l <side; l++) {
        for (unsigned c =0; c <side; c++) {
            graph_insertVertex(g, plateau_getPtr(i->p, l, c));

            if (l ==0)
                graph_insertEdge(g, &i->blackSide1, plateau_getPtr(i->p, l, c));
            else
                graph_insertEdge(g, plateau_getPtr(i->p, l -1, c), plateau_getPtr(i->p, l, c));

            if (c ==0)
                graph_insertEdge(g, &i->whiteSide1, plateau_getPtr(i->p, l, c));
            else
                graph_insertEdge(g, plateau_getPtr(i->p, l, c -1), plateau_getPtr(i->p, l, c));

            if (l ==side -1)
                graph_insertEdge(g, &i->blackSide2, plateau_getPtr(i->p, l, c));

            if (c ==side -1)
                graph_insertEdge(g, &i->whiteSide2, plateau_getPtr(i->p, l, c));

            if (l !=0 && c !=0)
                graph_insertEdge(g, plateau_getPtr(i->p, l, c), plateau_getPtr(i->p, l -1, c -1));
        }
    }
}

interface interface_create(unsigned side) {
    interface i =malloc(sizeof(struct s_interface));

    i->size =side;
    i->p =plateau_create(side, side);

    i->g =graph_create();
    interface_buildGraphPlateau(i, i->g);

    i->blackGroup =graph_create();
    graph_insertVertex(i->blackGroup, &i->blackSide1);
    graph_insertVertex(i->blackGroup, &i->blackSide2);

    i->whiteGroup =graph_create();
    graph_insertVertex(i->whiteGroup, &i->whiteSide1);
    graph_insertVertex(i->whiteGroup, &i->whiteSide2);

    int width =1600;
    int height =900;
    int dec =5;
    sdl_create(width, height, "HegGame");
    int margin =30;
    int wBox =(width -4 *margin) /3;
    int hBox =(height -4 *margin) /3;

    i->casePlayed =list_create();
    i->caseRedo =list_create();
    i->caseRedoColor =list_create();

    i->surface_ihm =sdl_newSurface(2 *wBox +margin, 2 *hBox +margin, margin, margin +dec, "ihm");
    interface_displayIhm(i);

    i->surface_blackGroup =sdl_newSurface(wBox, hBox, margin, 3 *margin +2 *hBox +dec, "blackGroup");
    interface_displayGraph(i, i->blackGroup, i->surface_blackGroup);

    i->surface_plateau =sdl_newSurface(wBox, hBox, 3 *margin +2 *wBox, margin +dec, "plateau");
    interface_displayPlateau(i);

    i->surface_graph =sdl_newSurface(wBox, hBox, 3 *margin +2 *wBox, 2 *margin +hBox +dec, "graph");
    interface_displayGraph(i, i->g, i->surface_graph);

    i->surface_whiteGroup =sdl_newSurface(wBox, hBox, 2 *margin +wBox, 3 *margin +2 *hBox +dec, "whiteGroup");
    interface_displayGraph(i, i->whiteGroup, i->surface_whiteGroup);

    i->reduceGraph =graph_create();
    interface_buildGraphPlateau(i, i->reduceGraph);
    i->surface_reduceGraph =sdl_newSurface(wBox, hBox, 3 *margin +2 *wBox, 3 *margin +2 *hBox +dec, "reduceGraph");
    interface_displayGraph(i, i->reduceGraph, i->surface_reduceGraph);
    /* interface_displayGraph(i, i->whiteGroup, i->surface_whiteGroup); */
    /* interface_drawPlateau(i->s, i->p); */
    i->redoActive =0;

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
    SDL_FreeSurface((*i)->surface_ihm);

    graph_destroy(&(*i)->reduceGraph);
    SDL_FreeSurface((*i)->surface_reduceGraph);

    list_destroy(&((*i)->casePlayed));
    list_destroy(&((*i)->caseRedo));
    list_destroy(&((*i)->caseRedoColor));

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


    // reduceGraph
    vertex vg1 =graph_findVertex(graph_getCollection(group), data);
    vertex vr1;

    if (! graph_onlyVertex(vg1)) {
        vr1 =graph_findVertex(graph_getCollection(i->reduceGraph), data);
        void* dvr1 =graph_getData(vr1);

        list_it it_vr1 =list_it_create(graph_getVertices(vr1));
        while (! list_it_end(it_vr1)) {
            vertex vr2 =list_it_get(it_vr1);
            void* dvr2 =graph_getData(vr2);

            if (graph_sameGroup(group, dvr1, dvr2)) {

                list_it it_vr2 =list_it_create(graph_getVertices(vr2));
                while (! list_it_end(it_vr2)) {
                    vertex vr3 =list_it_get(it_vr2);
                    void* dvr3 =graph_getData(vr3);

                    if (dvr1 !=dvr3) {
                        if (! graph_findVertex(graph_getVertices(vr1), dvr3))
                            graph_insertEdge(i->reduceGraph, dvr1, dvr3);
                    }

                    list_it_next(it_vr2);
                }
                list_it_destroy(&it_vr2);
                /* graph_delVertex(i->reduceGraph, dvr2); */
            }
            list_it_next(it_vr1);
        }

        void* ddel;
        do {
            ddel =NULL;

            it_vr1 =list_it_create(graph_getVertices(vr1));
            while (! list_it_end(it_vr1)) {
                vertex vr2 =list_it_get(it_vr1);
                void* dvr2 =graph_getData(vr2);

                if (graph_sameGroup(group, dvr1, dvr2)) {
                    if (graph_findVertex(graph_getCollection(i->reduceGraph), dvr2))
                        ddel =dvr2;
                }
                list_it_next(it_vr1);
            }
            list_it_destroy(&it_vr1);

            if (ddel)
                graph_delVertex(i->reduceGraph, ddel);
        } while (ddel);
    }
    // end reduceGraph



    list_pushBack(i->casePlayed, data);

    if (!list_empty(i->caseRedo) && !i->redoActive) {
        list_clean(i->caseRedo);
        list_clean(i->caseRedoColor);
    }

    i->redoActive =0;


    /* interface_majScreen(i); */
}

int interface_getPawn(interface i, unsigned line, unsigned column) {
    void* pawn =plateau_get(i->p, line, column);
    if (pawn ==&i->blackPawn)
        return interface_BLACK_PAWN;
    else if (pawn ==&i->whitePawn)
        return interface_WHITE_PAWN;
    else if (pawn ==NULL)
        return 0;
    else
        assert(0);
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

void interface_undo(interface i) {
    if (list_empty(i->casePlayed))
        return;

    void* dvr1 =list_back(i->casePlayed);
    void* pawn;
    for (unsigned l =0; l <i->size; l++) {
        for (unsigned c =0; c <i->size; c++) {
            if (plateau_getPtr(i->p, l, c) ==dvr1) {
                pawn =plateau_get(i->p, l, c);
                plateau_insert(i->p, l, c, NULL);
                goto next;
            }
        }
    }
    return;

    graph group;
    next:
    if (pawn ==&i->whitePawn) {
        group =i->whiteGroup;
        list_pushBack(i->caseRedoColor, &i->whitePawn);
    }
    else if (pawn ==&i->blackPawn) {
        group =i->blackGroup;
        list_pushBack(i->caseRedoColor, &i->blackPawn);
    }
    else
        assert(0);

    graph_delVertex(group, dvr1);
    



    /* vertex v =graph_findVertex(graph_getCollection(group), data); */
    /* graph_delVertex(v); */

    list_pushBack(i->caseRedo, list_back(i->casePlayed));
    list_popBack(i->casePlayed);

    // reduceGraph
    if (! list_empty(i->casePlayed)) {

        void* d2 =list_back(i->casePlayed);
        assert(d2);
        if (! graph_findVertex(graph_getCollection(i->reduceGraph), d2)) {
            graph_insertVertex(i->reduceGraph, d2);

            vertex vr1 =graph_findVertex(graph_getCollection(i->reduceGraph), dvr1);
            assert(vr1);
            vertex vr2 =graph_findVertex(graph_getCollection(i->reduceGraph), d2);
            assert(vr2);

            vertex vg2 =graph_findVertex(graph_getCollection(i->g), d2);

            list_it it_vg2 =list_it_create(graph_getVertices(vg2));
            while (! list_it_end(it_vg2)) {
                vertex vg21 =list_it_get(it_vg2);
                assert(vg21);
                void* dvg21 =graph_getData(vg21);
                assert(dvg21);

                list_it_next(it_vg2);
                if (graph_findVertex(graph_getCollection(i->reduceGraph), dvg21)) {
                    graph_insertEdge(i->reduceGraph, d2, dvg21);

                }
                /* if (! graph_neighbourVertex(i->g, dvr1, dvg21)) { */
                /*     graph_unlink(vr1, vg21); */
                /*     graph_insertEdge(i->reduceGraph, d2, dvg21); */
                /*  */
                /* } */
            }
            list_it_destroy(&it_vg2);

            list_it it_vr1 =list_it_create(graph_getVertices(vr1));
            while (! list_it_end(it_vr1)) {
                vertex vr11 =list_it_get(it_vr1);
                assert(vr11);
                void* dvr11 =graph_getData(vr11);
                assert(dvr11);

                list_it_next(it_vr1);
                if (! graph_neighbourVertex(i->g, dvr1, dvr11)) {
                    graph_unlink(vr1, vr11);

                    if (! graph_neighbourVertex(i->reduceGraph, d2, dvr11))
                        graph_insertEdge(i->reduceGraph, d2, dvr11);

                }
            }
            list_it_destroy(&it_vr1);
        }
    }

    return;
}

void interface_redo(interface i) {
    assert(list_size(i->caseRedo) ==list_size(i->caseRedoColor));
    i->redoActive =1;
    if (list_empty(i->caseRedo))
        return;

    void* data =list_back(i->caseRedo);
    void* pawn =list_back(i->caseRedoColor);
    for (unsigned l =0; l <i->size; l++) {
        for (unsigned c =0; c <i->size; c++) {
            if (plateau_getPtr(i->p, l, c) ==data) {
                if (pawn ==&i->whitePawn) {
                    interface_placePawn(i, interface_WHITE_PAWN, l, c);
                }
                else if (pawn ==&i->blackPawn) {
                    interface_placePawn(i, interface_BLACK_PAWN, l, c);
                }
                else
                    assert(0);

                list_popBack(i->caseRedo);
                list_popBack(i->caseRedoColor);
                return;
            }
        }
    }
    assert(0);
}

SDL_Rect interface_graphCase(interface i, SDL_Surface* area, void* data, int marginX, int marginY, int caseSize, int line, int column) {
    SDL_Rect pos;

    if (data ==NULL) {
        pos.x =(short)(0);
        pos.y =(short)(0);
        return pos;
    }
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
                pos.x =(short)(marginX +c *(2 *caseSize) -l *caseSize +(line -1) *caseSize);
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
    sdl_clean(area, SDL_WHITE);
    /* graph_print(g); */

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
    sdl_clean(i->surface_plateau, SDL_WHITE);

    /* plateau_print(i->p); */
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
    interface_displayIhm(i);
    interface_displayPlateau(i);
    /* interface_displayGraph(i, i->g, i->surface_graph); */
    interface_displayGraph(i, i->blackGroup, i->surface_blackGroup);
    interface_displayGraph(i, i->whiteGroup, i->surface_whiteGroup);
    interface_displayGraph(i, i->reduceGraph, i->surface_reduceGraph);

    /* interface_drawPlateau(i->s, i->p); */
}

SDL_Rect interface_ihmCasePos(interface i, int l, int c) {
    SDL_Surface* area =i->surface_ihm;

    int line =plateau_getNbLine(i->p);
    int column =plateau_getNbColumn(i->p);
    assert(line ==column);

    int caseHeight =area->h /(line +1);
    int caseSide =(int)(caseHeight /sqrt(3));

    int topX =area->w /2;
    int topY =caseHeight;
    SDL_Rect pos;
    pos.x =(short)(topX +(3 *caseSide *(c -l)) /2);
    pos.y =(short)(topY +(caseHeight *(l +c)) /2);

    return pos;
}

SDL_Rect sdl_whichCase(interface i, SDL_Rect pos) {
    SDL_Surface* area =i->surface_ihm;
    SDL_Rect posCase;
    if (pos.x >area->clip_rect.x && pos.x <area->clip_rect.x +area->w
            && pos.y >area->clip_rect.y && pos.y <area->clip_rect.y +area->h) {

        pos.x =(short)(pos.x -area->clip_rect.x);
        pos.y =(short)(pos.y -area->clip_rect.y);

        int line =plateau_getNbLine(i->p);
        int column =plateau_getNbColumn(i->p);
        int sizeCase =(area->h /(line +1)) /3;
        assert(line ==column);
        for (short l=0; l <line; l++) {
            for (short c=0; c <line; c++) {
                posCase =interface_ihmCasePos(i, l, c);
                if (pos.x >posCase.x -sizeCase && pos.x <posCase.x +sizeCase
                        && pos.y >posCase.y -sizeCase && pos.y <posCase.y +sizeCase) {
                    pos.x =c;
                    pos.y =l;
                    return pos;
                }
            }
        }
    }
    pos.x =-1;
    pos.y =-1;
    return pos;
}

void interface_ihm(interface i) {
    int continuer =1;
    int caseHeight =i->surface_ihm->h /((int)i->size +1);
    int rayPawn =caseHeight /3;
    SDL_Event event;
    SDL_Rect posCase;
    SDL_Rect square;
    SDL_Surface* pawn =SDL_CreateRGBSurface(SDL_HWSURFACE, 2 *rayPawn +2, 2 *rayPawn +2, 32, 0, 0, 0, 0);
    SDL_FillRect(pawn, NULL, SDL_RED);
    sdl_disk(pawn, rayPawn +1, rayPawn +1, rayPawn, SDL_WHITE);
    SDL_Rect posPawn;
    int mouseDown;
    int color;
    while (continuer) {
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                continuer =0;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym ==SDLK_q)
                    continuer =0;
                break;

            case SDL_MOUSEBUTTONDOWN:
                sdl_floodfill(pawn, rayPawn, rayPawn, SDL_WHITE, SDL_RED);
                switch (event.button.button) {
                    case SDL_BUTTON_RIGHT:
                        sdl_floodfill(pawn, rayPawn, rayPawn, SDL_BLACK, SDL_RED);
                    case SDL_BUTTON_LEFT:
                        posCase.x =(short)event.button.x;
                        posCase.y =(short)event.button.y;
                        square =sdl_whichCase(i, posCase);

                        if (square.y !=-1) {
                            if ((color =interface_getPawn(i, (unsigned)square.y, (unsigned)square.x)) !=0) {
                                if (plateau_getPtr(i->p, (unsigned)square.y, (unsigned)square.x)
                                        ==list_back(i->casePlayed)) {

                                    if (color ==interface_BLACK_PAWN)
                                        sdl_floodfill(pawn, rayPawn, rayPawn, SDL_BLACK, SDL_RED);
                                    else if (color ==interface_WHITE_PAWN)
                                        sdl_floodfill(pawn, rayPawn, rayPawn, SDL_WHITE, SDL_RED);
                                    else
                                        assert(0);

                                    interface_undo(i);
                                }
                                else
                                    color =0;
                            }
                        }
                        /* interface_majScreen(i); */
                        interface_displayIhm(i);
                        /* posPawn.x =(short)event.button.x; */
                        /* posPawn.y =(short)event.button.y; */
                        /* SDL_BlitSurface(pawn, NULL, screen, &posPawn); */
                        /* SDL_Flip(screen); */

                        mouseDown =1;
                        SDL_ShowCursor(SDL_DISABLE);
                        while (mouseDown) {
                            SDL_WaitEvent(&event);

                            switch (event.type) {
                                case SDL_MOUSEBUTTONUP:
                                    mouseDown =0;
                                    break;

                                case SDL_MOUSEMOTION:
                                    posPawn.x =(short)(event.motion.x -rayPawn +1);
                                    posPawn.y =(short)(event.motion.y -rayPawn +1);
                                    SDL_BlitSurface(i->surface_ihm, NULL, screen, &i->surface_ihm->clip_rect);
                                    SDL_SetColorKey(pawn, SDL_SRCCOLORKEY, SDL_RED);
                                    SDL_BlitSurface(pawn, NULL, screen, &posPawn);
                                    SDL_Flip(screen);
                                    break;

                                default:
                                    break;
                            }
                        }
                        posCase.x =(short)event.button.x;
                        posCase.y =(short)event.button.y;
                        square =sdl_whichCase(i, posCase);

                        if (square.y !=-1) {
                            if (interface_getPawn(i, (unsigned)square.y, (unsigned)square.x) ==0) {
                                if (color ==interface_BLACK_PAWN)
                                    interface_placePawn(i, interface_BLACK_PAWN, (unsigned)square.y, (unsigned)square.x);
                                else if (color ==interface_WHITE_PAWN)
                                    interface_placePawn(i, interface_WHITE_PAWN, (unsigned)square.y, (unsigned)square.x);
                                else
                                    if (event.button.button ==SDL_BUTTON_RIGHT)
                                        interface_placePawn(i, interface_BLACK_PAWN, (unsigned)square.y, (unsigned)square.x);
                                    else
                                        interface_placePawn(i, interface_WHITE_PAWN, (unsigned)square.y, (unsigned)square.x);

                            }
                        }
                        interface_majScreen(i);
                        break;

                    case SDL_BUTTON_WHEELDOWN:
                        interface_undo(i);
                        interface_majScreen(i);
                        break;

                    case SDL_BUTTON_WHEELUP:
                        interface_redo(i);
                        interface_majScreen(i);
                        break;

                    default:
                        break;
                }
                SDL_ShowCursor(SDL_ENABLE);
                break;

            default:
                break;
        }
    }
    SDL_FreeSurface(pawn);
}


void interface_displayIhm(interface i) {
    SDL_Surface* area =i->surface_ihm;
    sdl_clean(area, sdl_color(1, 1, 1));
    /* sdl_floodfill(area, 0, 0, sdl_color(1, 1, 1), SDL_BLACK); */
    /* sdl_pictureFont(area, "tableFont.jpg"); */

    int line =plateau_getNbLine(i->p);
    int column =plateau_getNbColumn(i->p);
    assert(line ==column);

    int caseHeight =area->h /(line +1);
    int caseSize =(int)(caseHeight /sqrt(3));

    int x;
    int y;
    int topX =area->w /2;
    int topY =caseHeight;
    void* data;
    for (int l =0 ;l <line ;l++) {
        for (int c =0 ;c <line ;c++) {
            x =topX +(3 *caseSize *(c -l)) /2;
            y =topY +(caseHeight *(l +c)) /2;
            sdl_hexagone(area, x, y, caseHeight);
            sdl_floodfill(area, x, y, sdl_color(211, 181, 129), SDL_BLACK);

            if (! list_empty(i->casePlayed) 
                    && plateau_getPtr(i->p, (unsigned)l, (unsigned)c) ==list_back(i->casePlayed))
                sdl_floodfill(area, x, y, sdl_color(0xDA, 0xA5, 0x20), SDL_BLACK);


            data =plateau_get(i->p, (unsigned)l, (unsigned)c);
            if (data) {
                if (data ==&i->blackPawn) {
                    sdl_disk(area, x, y, caseHeight /3, SDL_BLACK);
                }
                else {
                    sdl_disk(area, x, y, caseHeight /3, SDL_WHITE);
                }
            }
        }
    }
    
    SDL_Rect top =interface_ihmCasePos(i, 0, 0);
    SDL_Rect right =interface_ihmCasePos(i, 0, column -1);
    SDL_Rect down =interface_ihmCasePos(i, line -1, column -1);
    SDL_Rect left =interface_ihmCasePos(i, line -1, 0);
    int marge =20;

    sdl_line(area, top.x, top.y -caseHeight /2 -(int)(caseSize /(2 *sqrt(3))) -(int)(marge /sqrt(3)), 
            left.x -(caseSize) *2 -marge, left.y);

    sdl_line(area, top.x, top.y -caseHeight /2 -(int)(caseSize /(2 *sqrt(3))) -(int)(marge /sqrt(3)), 
            right.x +(caseSize) *2 +marge, right.y);

    sdl_line(area, down.x, down.y +caseHeight /2 +(int)(caseSize /(2 *sqrt(3))) +(int)(marge /sqrt(3)), 
            right.x +(caseSize) *2 +marge, right.y);

    sdl_line(area, down.x, down.y +caseHeight /2 +(int)(caseSize /(2 *sqrt(3))) +(int)(marge /sqrt(3)), 
            left.x -(caseSize) *2 -marge, left.y);

    sdl_line(area, top.x, top.y -caseHeight /2, 
            top.x, top.y -caseHeight /2 -(int)(caseSize /(2 *sqrt(3))) -(int)(marge /sqrt(3))); 

    sdl_line(area, down.x, down.y +caseHeight /2, 
            down.x, down.y +caseHeight /2 +(int)(caseSize /(2 *sqrt(3))) +(int)(marge /sqrt(3))); 

    sdl_line(area, left.x -caseSize, left.y, 
            left.x -(caseSize *2) -marge, left.y);

    sdl_line(area, right.x +caseSize, right.y, 
            right.x +(caseSize *2) +marge, right.y);

    sdl_floodfill(area, top.x +1, top.y -caseHeight /2 -1, SDL_BLACK, SDL_BLACK);
    sdl_floodfill(area, top.x -1, top.y -caseHeight /2 -1, SDL_WHITE, SDL_BLACK);
    sdl_floodfill(area, down.x +1, down.y +caseHeight /2 +1, SDL_WHITE, SDL_BLACK);
    sdl_floodfill(area, down.x -1, down.y +caseHeight /2 +1, SDL_BLACK, SDL_BLACK);
    sdl_floodfill(area, 0, 0, SDL_YELLOW, SDL_BLACK);

    SDL_BlitSurface(area, NULL, screen, &area->clip_rect);
    SDL_Flip(screen);
}

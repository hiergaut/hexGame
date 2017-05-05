#include "interface.h"
#include "plateau.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "backup.h"
#include <string.h>

struct s_interface {
    unsigned size;
    plateau p;
    int key;

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

    graph reduceGraph;

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
                /* graph_insertEdge(g, &i->blackSide1, plateau_getPtr(i->p, l, c)); */
                graph_insertEdge(g, &i->whiteSide1, plateau_getPtr(i->p, l, c));
            else
                graph_insertEdge(g, plateau_getPtr(i->p, l -1, c), plateau_getPtr(i->p, l, c));

            if (c ==0)
                /* graph_insertEdge(g, &i->whiteSide1, plateau_getPtr(i->p, l, c)); */
                graph_insertEdge(g, &i->blackSide1, plateau_getPtr(i->p, l, c));
            else
                graph_insertEdge(g, plateau_getPtr(i->p, l, c -1), plateau_getPtr(i->p, l, c));

            if (l ==side -1)
                /* graph_insertEdge(g, &i->blackSide2, plateau_getPtr(i->p, l, c)); */
                graph_insertEdge(g, &i->whiteSide2, plateau_getPtr(i->p, l, c));

            if (c ==side -1)
                /* graph_insertEdge(g, &i->whiteSide2, plateau_getPtr(i->p, l, c)); */
                graph_insertEdge(g, &i->blackSide2, plateau_getPtr(i->p, l, c));

            if (l !=0 && c !=side -1)
                graph_insertEdge(g, plateau_getPtr(i->p, l, c), plateau_getPtr(i->p, l -1, c +1));
        }
    }
}

interface interface_create(unsigned side) {
    interface i =malloc(sizeof(struct s_interface));

    i->size =side;
    i->p =plateau_create(side, side);
    i->key =0;

    i->g =graph_create();
    interface_buildGraphPlateau(i, i->g);

    i->blackGroup =graph_create();
    graph_insertVertex(i->blackGroup, &i->blackSide1);
    graph_insertVertex(i->blackGroup, &i->blackSide2);

    i->whiteGroup =graph_create();
    graph_insertVertex(i->whiteGroup, &i->whiteSide1);
    graph_insertVertex(i->whiteGroup, &i->whiteSide2);

    i->reduceGraph =graph_create();
    interface_buildGraphPlateau(i, i->reduceGraph);

    i->casePlayed =list_create();
    i->caseRedo =list_create();
    i->caseRedoColor =list_create();

    i->redoActive =0;



    return i;
}

void interface_destroy(interface* i) {
    plateau_destroy(&(*i)->p);
    graph_destroy(&(*i)->g);

    graph_destroy(&(*i)->blackGroup);
    graph_destroy(&(*i)->whiteGroup);


    graph_destroy(&(*i)->reduceGraph);

    list_destroy(&((*i)->casePlayed));
    list_destroy(&((*i)->caseRedo));
    list_destroy(&((*i)->caseRedoColor));












    free(*i);
    *i =NULL;
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

int interface_winner(interface i) {
    if (graph_sameGroup(i->whiteGroup, &i->whiteSide1, &i->whiteSide2))
        return interface_WHITE_PAWN;

    if (graph_sameGroup(i->blackGroup, &i->blackSide1, &i->blackSide2))
        return interface_BLACK_PAWN;

    return 0;
}

int interface_saveGame(interface i, const char* file) {
    catalog cat =catalog_create(file);
    backup_save(cat, &i->key, i->p, i->casePlayed, &i->whitePawn, &i->blackPawn);
    catalog_destroy(&cat);
    
    return i->key;
}

interface interface_restoreGame(int idGame, const char* file) {
    assert(idGame >0);
    catalog cat =catalog_create(file);

    interface i =interface_create((unsigned)backup_sidePlateau(cat, idGame));
    i->key =idGame;

    int pos =catalog_posIthOccurrence(cat, "\\game", idGame) +1;
    char str[CATALOG_BUFFER_MAX +1];
    catalog_getLine(cat, pos++, str);
    while (strcmp(str, "\\endgame")) {
        char color =str[6];
        int line;
        int column;
        sscanf(&str[8], "%d %d", &line, &column);
        /* printf("str ='%s'\n", str); */

        assert(color =='*' || color =='o');
        color =(color =='*') ?(interface_BLACK_PAWN) :(interface_WHITE_PAWN);

        interface_placePawn(i, color, (unsigned)line, (unsigned)column);
        /* printf("line =%d column =%d\n", line, column); */


        catalog_getLine(cat, pos++, str);
    }


    catalog_destroy(&cat);
    return i;
}

/* void interface_displayHistory() { */
/*     printf("History of previous game\n"); */
/* } */

int interface_undo(interface i) {
    if (list_empty(i->casePlayed))
        return 0;

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
    assert(0);

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

    if (pawn ==&i->blackPawn)
        return interface_BLACK_PAWN;
    if (pawn ==&i->whitePawn)
        return interface_WHITE_PAWN;
    assert(0);
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






int interface_getSide(interface i) {
    return (int)i->size;
}

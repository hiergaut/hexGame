#include "interface.h"
#include "plateau.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "backup.h"
#include <string.h>
#include "tree.h"

#define interface_ENABLE_IA_AUTOPLAY 1

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

void interface_buildGraphPlateauWithoutInterface(plateau p, void* whiteSide,
        void* whiteSide2, void* blackSide, void* blackSide2, graph g) {

    graph_insertVertex(g, whiteSide);
    graph_insertVertex(g, whiteSide2);
    graph_insertVertex(g, blackSide);
    graph_insertVertex(g, blackSide2);
    unsigned side =(unsigned)plateau_getNbLine(p);
    for (unsigned l =0; l <side; l++) {
        for (unsigned c =0; c <side; c++) {
            graph_insertVertex(g, plateau_getPtr(p, l, c));


            /* if (l ==0) */
            /*     graph_insertEdge(g, blackSide, plateau_getPtr(p, l, c)); */
            /* else */
            /*     graph_insertEdge(g, plateau_getPtr(p, l -1, c), plateau_getPtr(p, l, c)); */
            /*  */
            /* if (c ==0) */
            /*     graph_insertEdge(g, whiteSide, plateau_getPtr(p, l, c)); */
            /* else */
            /*     graph_insertEdge(g, plateau_getPtr(p, l, c -1), plateau_getPtr(p, l, c)); */
            /*  */
            /* if (l ==side -1) */
            /*     graph_insertEdge(g, blackSide2, plateau_getPtr(p, l, c)); */
            /*  */
            /* if (c ==side -1) */
            /*     graph_insertEdge(g, whiteSide2, plateau_getPtr(p, l, c)); */
            /*  */
            /* if (l !=0 && c !=side -1) */
            /*     graph_insertEdge(g, plateau_getPtr(p, l, c), plateau_getPtr(p, l -1, c +1)); */




            if (l ==0)
                graph_insertEdge(g, whiteSide, plateau_getPtr(p, l, c));
            else
                graph_insertEdge(g, plateau_getPtr(p, l -1, c), plateau_getPtr(p, l, c));

            if (c ==0)
                graph_insertEdge(g, blackSide, plateau_getPtr(p, l, c));
            else
                graph_insertEdge(g, plateau_getPtr(p, l, c -1), plateau_getPtr(p, l, c));

            if (l ==side -1)
                graph_insertEdge(g, whiteSide2, plateau_getPtr(p, l, c));

            if (c ==side -1)
                graph_insertEdge(g, blackSide2, plateau_getPtr(p, l, c));

            if (l !=0 && c !=side -1)
                graph_insertEdge(g, plateau_getPtr(p, l, c), plateau_getPtr(p, l -1, c +1));
        }
    }
}

void interface_buildGraphPlateau(interface i, graph g) {
    interface_buildGraphPlateauWithoutInterface(i->p, &i->whiteSide1, &i->whiteSide2,
            &i->blackSide1, &i->blackSide2, g);
    /* graph_insertVertex(g, &i->whiteSide1); */
    /* graph_insertVertex(g, &i->whiteSide2); */
    /* graph_insertVertex(g, &i->blackSide1); */
    /* graph_insertVertex(g, &i->blackSide2); */
    /* unsigned side =i->size; */
    /* for (unsigned l =0; l <side; l++) { */
    /*     for (unsigned c =0; c <side; c++) { */
    /*         graph_insertVertex(g, plateau_getPtr(i->p, l, c)); */
    /*  */
    /*         if (l ==0) */
    /*             #<{(| graph_insertEdge(g, &i->blackSide1, plateau_getPtr(i->p, l, c)); |)}># */
    /*             graph_insertEdge(g, &i->whiteSide1, plateau_getPtr(i->p, l, c)); */
    /*         else */
    /*             graph_insertEdge(g, plateau_getPtr(i->p, l -1, c), plateau_getPtr(i->p, l, c)); */
    /*  */
    /*         if (c ==0) */
    /*             #<{(| graph_insertEdge(g, &i->whiteSide1, plateau_getPtr(i->p, l, c)); |)}># */
    /*             graph_insertEdge(g, &i->blackSide1, plateau_getPtr(i->p, l, c)); */
    /*         else */
    /*             graph_insertEdge(g, plateau_getPtr(i->p, l, c -1), plateau_getPtr(i->p, l, c)); */
    /*  */
    /*         if (l ==side -1) */
    /*             #<{(| graph_insertEdge(g, &i->blackSide2, plateau_getPtr(i->p, l, c)); |)}># */
    /*             graph_insertEdge(g, &i->whiteSide2, plateau_getPtr(i->p, l, c)); */
    /*  */
    /*         if (c ==side -1) */
    /*             #<{(| graph_insertEdge(g, &i->whiteSide2, plateau_getPtr(i->p, l, c)); |)}># */
    /*             graph_insertEdge(g, &i->blackSide2, plateau_getPtr(i->p, l, c)); */
    /*  */
    /*         if (l !=0 && c !=side -1) */
    /*             graph_insertEdge(g, plateau_getPtr(i->p, l, c), plateau_getPtr(i->p, l -1, c +1)); */
    /*     } */
    /* } */
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

void interface_placePawnInGraphAndGroup(void* data, graph g, graph group) {
    graph_insertVertex(group, data);

    vertex vGraph =graph_findVertex(graph_getCollection(g), data);
    assert(vGraph);

    vertex vGroup =graph_findVertex(graph_getCollection(group), data);
    (void)vGroup;
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

    interface_placePawnInGraphAndGroup(data, i->g, group);
    /* graph_insertVertex(group, data); */
    /*  */
    /* vertex vGraph =graph_findVertex(graph_getCollection(i->g), data); */
    /* assert(vGraph); */
    /*  */
    /* vertex vGroup =graph_findVertex(graph_getCollection(group), data); */
    /* assert(vGroup); */
    /*  */
    /* list_it it_vertices =list_it_create(graph_getVertices(vGraph)); */
    /* while (! list_it_end(it_vertices)) { */
    /*     vertex vGraphVertices =list_it_get(it_vertices); */
    /*  */
    /*     void* caseCur =graph_getData(vGraphVertices); */
    /*  */
    /*     if (graph_findVertex(graph_getCollection(group), caseCur)) { */
    /*         graph_insertEdge(group, data, caseCur); */
    /*     } */
    /*  */
    /*     list_it_next(it_vertices); */
    /* } */
    /* list_it_destroy(&it_vertices); */


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
            (void)vr1;
            assert(vr1);
            vertex vr2 =graph_findVertex(graph_getCollection(i->reduceGraph), d2);
            (void)vr2;
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
    return -1;
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


// robot
struct s_game {
    int colorPlayerTurn;
    int value;
    int line;
    int column;
};
typedef struct s_game* game;

game game_create(int colorPlayerTurn, int line, int column) {
    game new =malloc(sizeof(struct s_game));

    new->colorPlayerTurn =colorPlayerTurn;
    new->value =0;
    new->line =line;
    new->column =column;

    return new;
}

void game_destroy(game* g) {
    free(*g);
    *g =NULL;
}

int game_switchPlayer(int color) {
    if (color ==interface_WHITE_PAWN)
        return interface_BLACK_PAWN;
    return interface_WHITE_PAWN;
}

bool game_winner(interface i, graph whiteGroup, graph blackGroup) {
    /* (void)blackPawn; */
    /* int side =plateau_getNbLine(p); */
    /* void* color; */
    /* int whiteSide, whiteSide2, blackSide, blackSide2; */
    /*  */
    /* graph g =graph_create(); */
    /* interface_buildGraphPlateauWithoutInterface(p, &whiteSide, &whiteSide2,  */
    /*         &blackSide, &blackSide2, g); */
    /*  */
    /* graph whiteGroup =graph_create(); */
    /* graph_insertVertex(whiteGroup, &whiteSide); */
    /* graph_insertVertex(whiteGroup, &whiteSide2); */
    /*  */
    /* graph blackGroup =graph_create(); */
    /* graph_insertVertex(blackGroup, &blackSide); */
    /* graph_insertVertex(blackGroup, &blackSide2); */
    /*  */
    /* for (int l =0; l <side; l++) { */
    /*     for (int c =0; c <side; c++) { */
    /*         // if pawn here */
    /*         if ((color =plateau_get(p, (unsigned)l, (unsigned)c))) { */
    /*             void* data =plateau_getPtr(p, (unsigned)l, (unsigned)c); */
    /*             graph group =(color ==whitePawn) ?(whiteGroup) :(blackGroup); */
    /*  */
    /*             interface_placePawnInGraphAndGroup(data, g, group); */
    /*         } */
    /*     } */
    /* } */

    int r =0;
    if (graph_sameGroup(whiteGroup, &i->whiteSide1, &i->whiteSide2))
        r =interface_WHITE_PAWN;

    if (graph_sameGroup(blackGroup, &i->blackSide1, &i->blackSide2))
        r =interface_BLACK_PAWN;

    /* graph_destroy(&g); */
    /* graph_destroy(&whiteGroup); */
    /* graph_destroy(&blackGroup); */

    return r;
}

void game_makeLeaf(Node n) {
    if (tree_isLeaf(n)) {
        game g =tree_getData(n);

        if (g->colorPlayerTurn ==interface_WHITE_PAWN)
            g->value =1;
        else
            g->value =-1;
    }
}

void game_print(Node n);

int game_getValue(Node n) {
    assert(n);
    game g =tree_getData(n);
    return g->value;
}

void game_mergeValue(Node n) {
    assert(game_getValue(n));
    /* printf("merge"); */
    /* game_print(n); */
    /* n =tree_getFather(n); */
    int value;
    int prevValue;
    game g =NULL;
    while ((value =game_getValue(n)) && (n =tree_getFather(n))) prevValue =value;
    if (n) {
        /* printf("\tvalueSon =%d", prevValue); */
        /* printf("\t\tblank father"); */
        /* game_print(n); */

        g =tree_getData(n);

        if (g->colorPlayerTurn ==interface_WHITE_PAWN) {
            if (prevValue ==-1) {
                g->value =-1;
            }
        }
        else
            if (prevValue ==1)
                g->value =1;
    }
    /* else */
        /* printf("already ROOT"); */

    /* printf("\n"); */
    if (n) {
        if (g->value) {
            game_mergeValue(n);
        }
        else {
            Node child;
            int max;
            int min;
            if ((child =tree_getChild(n))) {
                if ((max =min =game_getValue(child))) {
                    while ((child =tree_getBrother(child))) {
                        value =game_getValue(child);
                        if (! value)
                            return;
                        if (value >max)
                            max =value;
                        if (value <min)
                            min =value;
                    }
                }
            }
            g->value =(g->colorPlayerTurn ==interface_WHITE_PAWN) ?(min) :(max);
        }
    }
}


void game_makeNode(Node n) {
    game g =tree_getData(n);
    int min;
    int max;
    // virgin
    if (! g->value) {
        Node child;
        // have least one child
        if ((child =tree_getChild(n))) {
            // already affected
            if ((max =min =game_getValue(child))) {

                while ((child =tree_getBrother(child))) {
                    int value =game_getValue(child);
                    if (! value)
                        return;

                    if (value >max)
                        max =value;
                    if (value <min)
                        min =value;

                }
            }
            g->value =(g->colorPlayerTurn ==interface_WHITE_PAWN) ?(min) :(max);
        }

    }
}


void game_mergeTree(interface i, Root root, plateau p, graph g, graph whiteGroup, graph blackGroup, list casePlayed, int* nbLeaf) {
    (void)i;
    (void)root;

    game parentGame =tree_getData(root);
    int futurePlayer =game_switchPlayer(parentGame->colorPlayerTurn);
    void* pawn =(parentGame->colorPlayerTurn ==interface_WHITE_PAWN) ?(&i->whitePawn) :(&i->blackPawn);

    if (! game_winner(i, whiteGroup, blackGroup)) {
        for (unsigned l =0; l <i->size; l++) {
            for (unsigned c =0; c <i->size; c++) {
                if (! plateau_get(p, l, c)) {
                    plateau_insert(p, l, c, pawn);
                    void* data =plateau_getPtr(p, (unsigned)l, (unsigned)c);
                    if (pawn ==&i->whitePawn)
                        interface_placePawnInGraphAndGroup(data, g, whiteGroup);
                    else
                        interface_placePawnInGraphAndGroup(data, g, blackGroup);
                    list_pushBack(casePlayed, data);

                    game futureGame =game_create(futurePlayer, (int)l, (int)c);
                    game_mergeTree(i, add_child(root, root, futureGame), p, g, whiteGroup, blackGroup, casePlayed, nbLeaf);


                    // undo
                    plateau_insert(p, l, c, NULL);
                    data =list_back(casePlayed);
                    if (pawn ==&i->whitePawn)
                        graph_delVertex(whiteGroup, data);
                    else
                        graph_delVertex(blackGroup, data);
                    list_popBack(casePlayed);
                }
            }
        }
    }
    else {
        if (parentGame->colorPlayerTurn ==interface_WHITE_PAWN)
            parentGame->value =1;
        else
            parentGame->value =-1;
        *nbLeaf =*nbLeaf +1;
    }


    /* traverse_tree(root, game_makeLeaf); */
    /* tree_widthBrowse(root, game_print); */
    /* tree_mapLeaf(root, game_mergeValue); */
    /* while (! game_getValue(root)) */
    /*     tree_mapInfix(root, game_makeNode); */

        /* traverse_tree(root, game_makeNode); */
        /* tree_widthBrowse(root, game_makeNode); */
        /* traverse_tree(root, game_makeNode); */
        /* traverse_tree(root, game_print); */
}

void printColor3(const char* str ,int id) {
	int color =id %15;
	if (color ==0)
		color =0;
	else if (color ==1)
		color =7;
	else if (color <8)
		color =31 +color -2;
	else
		color =41 +color -8;

	/* sprintf(print ,"\x1B[%dm%d\x1B[0m" ,color ,id); */
	printf("\x1B[%dm%s\x1B[0m" ,color ,str);
	/* return print; */
}

void game_print(Node n) {
    game g =tree_getData(n);
    if (tree_firstChild(n)) {
        printColor3(":", (int)(long)tree_parent(n));
        printf(" ");
    }

    printf("%d", g->colorPlayerTurn);
    /* if (g->colorPlayerTurn ==interface_WHITE_PAWN) */
    /*     printf("\x1B[7m%d\x1B[0m", g->colorPlayerTurn); */
    /* else */
    /*     printf("%d", g->colorPlayerTurn); */
    printColor3(":", (int)(long)n);
    printf("%d ", g->value);

    if (tree_lastChild(n)) {
        printColor3(":", (int)(long)tree_parent(n));
    }
}

void game_destroyNode(Node n) {
    game g =tree_getData(n);
    game_destroy(&g);
}

void game_destroyTree(Node n) {
    /* tree_widthBrowse(n, game_destroyNode); */
    tree_mapInfix(n, game_destroyNode);
}

unsigned long long factorial(int n) {
    assert(n >0);
    unsigned long long N =(unsigned long long)n;
    unsigned long long r =N;
    while (--N) r *=N;
    return r;
}

int interface_botTakePlace(interface i, int colorPawn) {
    int side =(int)i->size;
    int line;
    int column;
    int caseRemaining =side *side -(int)list_size(i->casePlayed);
    if (caseRemaining >10) {
        printf("Too leaf\n");

        do {
            line =rand() %side;
            column =rand() %side;
        } while (interface_getPawn(i, (unsigned)line, (unsigned)column));

        interface_placePawn(i, colorPawn, (unsigned)line, (unsigned)column);
    }
    else {
        void* color;
        /* int whiteSide, whiteSide2, blackSide, blackSide2; */
        plateau p =plateau_copy(i->p);

        graph g =graph_create();
        interface_buildGraphPlateauWithoutInterface(p, &i->whiteSide1, &i->whiteSide2, 
                &i->blackSide1, &i->blackSide2, g);

        graph whiteGroup =graph_create();
        graph_insertVertex(whiteGroup, &i->whiteSide1);
        graph_insertVertex(whiteGroup, &i->whiteSide2);

        graph blackGroup =graph_create();
        graph_insertVertex(blackGroup, &i->blackSide1);
        graph_insertVertex(blackGroup, &i->blackSide2);

        list casePlayed =list_create();

        for (int l =0; l <side; l++) {
            for (int c =0; c <side; c++) {
                // if pawn here
                if ((color =plateau_get(p, (unsigned)l, (unsigned)c))) {
                    void* data =plateau_getPtr(p, (unsigned)l, (unsigned)c);
                    graph group =(color ==&i->whitePawn) ?(whiteGroup) :(blackGroup);

                    interface_placePawnInGraphAndGroup(data, g, group);
                    list_pushBack(casePlayed, data);
                }
            }
        }

        /* assert(! graph_sameGroup(whiteGroup, &i->whiteSide1, &i->whiteSide2)); */
        /* assert(! graph_sameGroup(blackGroup, &i->blackSide1, &i->blackSide2)); */


        Root root =create_tree();
        game ga =game_create(colorPawn, 0, 0);

        root =add_child(root, NULL, ga);
        /* tree_widthBrowse(root, game_print); */

        int nbLeaf =0;
        game_mergeTree(i, root, p, g, whiteGroup, blackGroup, casePlayed, &nbLeaf);
        printf("nbLeaf =%d\n", nbLeaf);
        printf("factorial %d =%lld\n", caseRemaining, factorial(caseRemaining));
        /* tree_widthBrowse(root, game_print); */


        while (! game_getValue(root)) {
            tree_mapLeaf(root, game_mergeValue);
            /* tree_widthBrowse(root, game_print); */
        }
        /* tree_mapLeaf(root, game_mergeValue); */
        /* tree_mapLeaf(root, game_mergeValue); */
        /* tree_mapLeaf(root, game_mergeValue); */
        /* tree_mapLeaf(root, game_mergeValue); */
        /* tree_mapLeaf(root, game_mergeValue); */
        /* tree_mapLeaf(root, game_mergeValue); */
        /* } */

        int value =(colorPawn ==interface_WHITE_PAWN) ?(-1) :(1);
        /* if (colorPawn ==interface_BLACK_PAWN) { */
        if (game_getValue(root) !=value) {
            printf("AI :FUCK off! \\) o_o \\) ^ _|_|_\n");
            /* int line; */
            /* int column; */
            do {
                line =rand() %side;
                column =rand() %side;
            } while (interface_getPawn(i, (unsigned)line, (unsigned)column));

            interface_placePawn(i, colorPawn, (unsigned)line, (unsigned)column);
            /* Node nChild =tree_getChild(root); */
            /* game gChild =tree_getData(nChild); */
            /* interface_placePawn(i, colorPawn, (unsigned)gChild->line, (unsigned)gChild->column); */
            /* printf("insert %d,%d\n", gChild->line, gChild->column); */
        }
        else {
            Node nChild =tree_getChild(root);
            assert(nChild);
            game gChild =tree_getData(nChild);
            assert(gChild);
            if (gChild->value ==value) {
                /* plateau_insert(i->p, (unsigned)gChild->line, (unsigned)gChild->column, &i->blackPawn); */
                interface_placePawn(i, colorPawn, (unsigned)gChild->line, (unsigned)gChild->column);
                printf("insert %d,%d\n", gChild->line, gChild->column);

                line =gChild->line;
                column =gChild->column;
            }
            else {
                while ((nChild =tree_getBrother(nChild))) {
                    gChild =tree_getData(nChild);
                    if (gChild->value ==value) {
                        /* plateau_insert(i->p, (unsigned)gChild->line, (unsigned)gChild->column, &i->blackPawn); */
                        interface_placePawn(i, colorPawn, (unsigned)gChild->line, (unsigned)gChild->column);
                        printf("insert %d,%d\n", gChild->line, gChild->column);

                        line =gChild->line;
                        column =gChild->column;
                        break;
                    }
                }
                assert(gChild);
            }
        }


        game_destroyTree(root);

        /* game_destroy(&g); */
        destroy_tree(root);


        graph_destroy(&g);
        graph_destroy(&whiteGroup);
        graph_destroy(&blackGroup);

        list_destroy(&casePlayed);

    }
    printf("line =%d, column =%d\n", line, column);
    printf("side =%d\n", side);
    return line *side +column;
}






int interface_getSide(interface i) {
    return (int)i->size;
}

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

/* #define interface_ENABLE_IA_AUTOPLAY 1 */

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
    printf("restore file ='%s'\n", file);
    FILE* f =fopen(file, "r");
    if (! f) {
        perror(file);
        return NULL;
    }
    fclose(f);

    catalog cat =catalog_create(file);

    interface i =interface_create((unsigned)backup_sidePlateau(cat, idGame));
    i->key =idGame;

    assert(idGame <=catalog_nbOccurrence(cat, "\\hex"));
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

int interface_edge(interface i, void* data) {
    return (data ==&i->whiteSide1) || (data ==&i->whiteSide2)
        || (data ==&i->blackSide1) || (data ==&i->blackSide2);
}

struct s_rank {
    int rank;
    int own;
    int other;
};

void interface_botBridge(interface i, int colorBotPawn, int* line, int* col) {
    int l;
    int c;
    struct s_rank ranking[i->size][i->size];
    for (l =0; l <(int)i->size; l++) {
        for (c =0; c <(int)i->size; c++) {
            ranking[l][c].rank =0;
            ranking[l][c].own =0;
            ranking[l][c].other =0;
        }
    }

    graph opponentGroup =(colorBotPawn ==interface_WHITE_PAWN) ?(i->blackGroup) :(i->whiteGroup);

    // for each pawn in versus group
    list_it it_vog =list_it_create(graph_getCollection(opponentGroup));
    while (! list_it_end(it_vog)) {
        vertex vog =list_it_get(it_vog);
        assert(vog);
        void* dv =graph_getData(vog);
        assert(dv);

        if (! interface_edge(i, dv)) {
            vertex vg=graph_findVertex(graph_getCollection(i->g), dv);
            assert(vg);

            // for each neighbor in graph
            list_it it_vg =list_it_create(graph_getVertices(vg));
            while (! list_it_end(it_vg)) {
                vertex vg2 =list_it_get(it_vg);
                assert(vg2);
                void* dvg2 =graph_getData(vg2);
                assert(dvg2);

                // if empty neighbor
                if (! interface_edge(i, dvg2)) {
                    if (! plateau_searchPtrCaseData(i->p, dvg2)) {

                        /* plateau_searchPtrCasePos(i->p, dvg2, &l, &c); */
                        /* ranking[l][c].rank++; */
                        /* ranking[l][c].other =1; */


                        // for each neighbor of neighbor
                        list_it it_vg2 =list_it_create(graph_getVertices(vg2));
                        while (! list_it_end(it_vg2)) {
                            vertex vg3 =list_it_get(it_vg2);
                            assert(vg3);
                            void* dvg3 =graph_getData(vg3);
                            assert(dvg3);

                            // if empty neighbor^2
                            if (! interface_edge(i, dvg3)) {
                                if (! plateau_searchPtrCaseData(i->p, dvg3)) {
                                    if (graph_neighbourVertex(i->g, dvg3, dv)) {

                                        // for each neighbor ^3
                                        list_it it_vg3 =list_it_create(graph_getVertices(vg3));
                                        while (! list_it_end(it_vg3)) {
                                            vertex vg4 =list_it_get(it_vg3);
                                            assert(vg4);
                                            void* dvg4 =graph_getData(vg4);
                                            assert(dvg4);

                                            if (! interface_edge(i, dvg4)) {
                                                if (! plateau_searchPtrCaseData(i->p, dvg4)) {
                                                    if (graph_neighbourVertex(i->g, dvg4, dvg2)) {
                                                        /* plateau_searchPtrCasePos(i->p, dvg2, &l, &c); */
                                                        /* ranking[l][c].rank++; */
                                                        /* ranking[l][c].other =1; */
                                                        /*  */
                                                        /* plateau_searchPtrCasePos(i->p, dvg3, &l, &c); */
                                                        /* ranking[l][c].rank++; */
                                                        /* ranking[l][c].other =1; */

                                                        plateau_searchPtrCasePos(i->p, dvg4, &l, &c);
                                                        ranking[l][c].rank++;
                                                        ranking[l][c].other =1;

                                                    }
                                                }
                                            }
                                            /* else if (graph_neighbourVertex(i->g, dvg3, &i->whiteSide1) || graph_neighbourVertex(i->g, dvg3, &i->whiteSide2)) { */
                                            /*     plateau_searchPtrCasePos(i->p, dvg3, &l, &c); */
                                            /*     ranking[l][c].rank +=2; */
                                            /*     ranking[l][c].other =1; */
                                            /* } */

                                            list_it_next(it_vg3);
                                        }
                                        list_it_destroy(&it_vg3);
                                    }
                                }
                            }
                            list_it_next(it_vg2);
                        }
                        list_it_destroy(&it_vg2);
                    }
                }
                list_it_next(it_vg);
            }
            list_it_destroy(&it_vg);
        }
        list_it_next(it_vog);
    }
    list_it_destroy(&it_vog);



    graph botGroup =(colorBotPawn ==interface_WHITE_PAWN) ?(i->whiteGroup) :(i->blackGroup);
    
    // for each bot's pawn
    list_it it_vbg =list_it_create(graph_getCollection(botGroup));
    while (! list_it_end(it_vbg)) {
        vertex vbg =list_it_get(it_vbg);
        assert(vbg);
        void* dv =graph_getData(vbg);
        assert(dv);

        if (! interface_edge(i, dv)) {
            vertex vg=graph_findVertex(graph_getCollection(i->g), dv);
            assert(vg);

            // for each neighbor in graph
            list_it it_vg =list_it_create(graph_getVertices(vg));
            while (! list_it_end(it_vg)) {
                vertex vg2 =list_it_get(it_vg);
                assert(vg2);
                void* dvg2 =graph_getData(vg2);
                assert(dvg2);

                // if empty neighbor
                if (! interface_edge(i, dvg2)) {
                    if (! plateau_searchPtrCaseData(i->p, dvg2)) {

                        /* plateau_searchPtrCasePos(i->p, dvg2, &l, &c); */
                        /* ranking[l][c].rank++; */
                        /* ranking[l][c].own =1; */

                        // for each neighbor of neighbor
                        list_it it_vg2 =list_it_create(graph_getVertices(vg2));
                        while (! list_it_end(it_vg2)) {
                            vertex vg3 =list_it_get(it_vg2);
                            assert(vg3);
                            void* dvg3 =graph_getData(vg3);
                            assert(dvg3);

                            // if empty neighbor^2
                            if (! interface_edge(i, dvg3)) {
                                if (! plateau_searchPtrCaseData(i->p, dvg3)) {
                                    // if also neighbor of first
                                    if (graph_neighbourVertex(i->g, dvg3, dv)) {

                                        // for each neighbor ^3
                                        list_it it_vg3 =list_it_create(graph_getVertices(vg3));
                                        while (! list_it_end(it_vg3)) {
                                            vertex vg4 =list_it_get(it_vg3);
                                            assert(vg4);
                                            void* dvg4 =graph_getData(vg4);
                                            assert(dvg4);

                                            if (! interface_edge(i, dvg4)) {
                                                if (! plateau_searchPtrCaseData(i->p, dvg4)) {

                                                    if (graph_neighbourVertex(i->g, dvg4, dvg2)) {
                                                        /* plateau_searchPtrCasePos(i->p, dvg2, &l, &c); */
                                                        /* ranking[l][c]++; */
                                                        plateau_searchPtrCasePos(i->p, dvg4, &l, &c);
                                                        ranking[l][c].rank++;
                                                        ranking[l][c].own =1;

                                                        /* plateau_searchPtrCasePos(i->p, dvg3, &l, &c); */
                                                        /* ranking[l][c].rank++; */
                                                        /* ranking[l][c].own =1; */
                                                        /*  */
                                                        /* plateau_searchPtrCasePos(i->p, dvg2, &l, &c); */
                                                        /* ranking[l][c].rank++; */
                                                        /* ranking[l][c].own =1; */
                                                        /*  */
                                                        /* if (graph_neighbourVertex(i->g, dvg4, &i->whiteSide1) || graph_neighbourVertex(i->g, dvg4, &i->whiteSide2)) { */
                                                        /*     plateau_searchPtrCasePos(i->p, dvg4, &l, &c); */
                                                        /*     ranking[l][c]++; */
                                                        /* } */
                                                    }
                                                }
                                            }
                                            /* else if (graph_neighbourVertex(i->g, dvg3, &i->blackSide1) || graph_neighbourVertex(i->g, dvg3, &i->blackSide2)) { */
                                            /*     plateau_searchPtrCasePos(i->p, dvg3, &l, &c); */
                                            /*     ranking[l][c].rank +=2; */
                                            /*     ranking[l][c].own =1; */
                                            /* } */
                                            list_it_next(it_vg3);
                                        }
                                        list_it_destroy(&it_vg3);
                                    }
                                }
                            }
                            list_it_next(it_vg2);
                        }
                        list_it_destroy(&it_vg2);
                    }
                }
                list_it_next(it_vg);
            }
            list_it_destroy(&it_vg);
        }
        list_it_next(it_vbg);
    }
    list_it_destroy(&it_vbg);

    
    int max =0;
    int lmax;
    int cmax;
    for (l =0; l <(int)i->size; l++) {
        for (c =0; c <(int)i->size; c++) {
            if (plateau_get(i->p, (unsigned)l, (unsigned)c)) {
                printf(" ");
            }
            else {
                if (ranking[l][c].own && ranking[l][c].other)
                    printf("\x1B[33m%d\x1B[0m", ranking[l][c].rank);
                else if (ranking[l][c].own)
                    printf("\x1B[32m%d\x1B[0m", ranking[l][c].rank);
                else if (ranking[l][c].other)
                    printf("\x1B[31m%d\x1B[0m", ranking[l][c].rank);
                else
                    printf("%d", ranking[l][c].rank);

            }

            if (ranking[l][c].rank >=max) {
                lmax =l;
                cmax =c;
                max =ranking[l][c].rank;
            }
        }
        printf("\n");
    }

    interface_placePawn(i, colorBotPawn, (unsigned)lmax, (unsigned)cmax);
    *line =lmax;
    *col =cmax;
}

void interface_botCutSmallerWay(interface i, int colorBotPawn, int* line, int* col) {
    /* int opponentColor; */
    /* graph botGroup; */
    /* graph opponentGroup; */
    /* (void)opponentColor; */
    /* (void)botGroup; */
    /* (void)opponentGroup; */
    /* if (colorBotPawn ==interface_WHITE_PAWN) { */
    /*     opponentColor =interface_BLACK_PAWN; */
    /*  */
    /*     botGroup =i->whiteGroup; */
    /*     opponentGroup =i->blackGroup; */
    /* } */
    /* else { */
    /*     opponentColor =interface_WHITE_PAWN; */
    /*  */
    /*     botGroup =i->blackGroup; */
    /*     opponentGroup =i->whiteGroup; */
    /* } */

    int len;
    int minLen =1000;
    void* minData;
    void* minData2;
    graph minWallGroup;
    int cptOnlyWhite =0;
    int cptOnlyBlack =0;

    /* plateau_print(i->p); */
    /* graph_print(i->reduceGraph); */

    // for each vertex in reduce graph
    list_it it_vrd =list_it_create(graph_getCollection(i->reduceGraph));
    while (! list_it_end(it_vrd)) {
        vertex vrd =list_it_get(it_vrd);
        assert(vrd);
        void* dvrd =graph_getData(vrd);
        assert(dvrd);

        // color of case
        void* cvrd =NULL;
        // if case not empty
        if (interface_edge(i, dvrd)) {
            if (dvrd ==&i->whiteSide1 || dvrd ==&i->whiteSide2)
                cvrd =&i->whitePawn;
            else
                cvrd =&i->blackPawn;
        }
        /* if (cvrd || (cvrd =plateau_searchPtrCaseData(i->p, dvrd))) { */
        if ((cvrd || (cvrd =plateau_searchPtrCaseData(i->p, dvrd))) && cvrd !=&i->blackPawn) {

            // for each vertex in reduce graph
            list_it it_vrd2 =list_it_create(graph_getCollection(i->reduceGraph));
            while (! list_it_end(it_vrd2)) {
                vertex vrd2 =list_it_get(it_vrd2);
                assert(vrd2);
                void* dvrd2 =graph_getData(vrd2);
                assert(dvrd2);

                // if not a same case, and same color first
                if (dvrd !=dvrd2) {
                    void* cvrd2 =NULL;
                    if (interface_edge(i, dvrd2)) {
                        if (dvrd2 ==&i->whiteSide1 || dvrd2 ==&i->whiteSide2)
                            cvrd2 =&i->whitePawn;
                        else
                            cvrd2 =&i->blackPawn;
                    }
                    if (cvrd2 || (cvrd2 =plateau_searchPtrCaseData(i->p, dvrd2))) {
                        /* assert(cvrd ==cvrd2); */
                        if (cvrd ==cvrd2) {
                            if (cvrd2 ==&i->whitePawn) {
                                cptOnlyWhite++;
                                printf("\x1B[7mwhite\x1B[0m :");
                            }
                            else {
                                cptOnlyBlack++;
                                printf("black :");
                            }


                            graph wallGroup =(cvrd2 ==&i->whitePawn) ?(i->blackGroup) :(i->whiteGroup);
                            len =graph_smallerWay(i->reduceGraph, wallGroup, dvrd, dvrd2);
                            printf("\tlen =%d", len);

                            if (len <minLen) {
                                minLen =len;
                                minData =dvrd;
                                minData2 =dvrd2;
                                minWallGroup =wallGroup;
                                printf("\tminLen =%d", minLen);
                            }

                            if (! (interface_edge(i, dvrd) || interface_edge(i, dvrd2))) {
                                plateau_searchPtrCasePos(i->p, dvrd, line, col);
                                printf("\t%d %d ->", *line, *col);
                                plateau_searchPtrCasePos(i->p, dvrd2, line, col);
                                printf("%d %d", *line, *col);
                                printf(" =%d", len);
                            }
                                printf("\n");
                        }
                    }
                }


                list_it_next(it_vrd2);
            }
            list_it_destroy(&it_vrd2);

        }
        list_it_next(it_vrd);
    }
    list_it_destroy(&it_vrd);
    assert(minLen !=1000);


    printf("minLen %d\n", minLen);
    int minDataLine =-1;
    int minDataColumn =-1;
    int whiteSide1 =0;
    int whiteSide2 =0;
    int blackSide1 =0;
    int blackSide2 =0;
    if (interface_edge(i, minData)) {
        if (minData ==&i->whiteSide1 || minData ==&i->whiteSide2)
            if (minData ==&i->whiteSide1) {
                printf("whiteSide1");
                whiteSide1 =1;
            }
            else {
                printf("whiteSide2");
                whiteSide2 =1;
            }
        else
            if (minData ==&i->blackSide1) {
                printf("blackSide1");
                blackSide1 =1;
            }
            else {
                printf("blackSide2");
                blackSide2 =1;
            }
        printf("\n");
    }
    else {
        plateau_searchPtrCasePos(i->p, minData, &minDataLine, &minDataColumn);
        printf("minData %d %d\n", minDataLine, minDataColumn);
    }


    int minData2Line =-1;
    int minData2Column =-1;
    if (interface_edge(i, minData2)) {
        if (minData2 ==&i->whiteSide1 || minData2 ==&i->whiteSide2)
            if (minData2 ==&i->whiteSide1) {
                printf("whiteSide1");
                whiteSide1 =2;
            }
            else {
                printf("whiteSide2");
                whiteSide2 =2;
                }
        else
            if (minData2 ==&i->blackSide1) {
                printf("blackSide1");
                blackSide1 =2;
            }
            else {
                printf("blackSide2");
                blackSide2 =2;
            }
        printf("\n");
    }
    else {
        plateau_searchPtrCasePos(i->p, minData2, &minData2Line, &minData2Column);
        printf("minData2 %d %d\n", minData2Line, minData2Column);
    }

    int middleLen =minLen /2 +1;
    if (middleLen ==0) {
        printf("middleLen 0 ->1\n");
        middleLen =1;
    }
    printf("middleLen =%d\n", middleLen);

    /* void* middleWay =graph_middleWay(i->reduceGraph, minWallGroup, minData, minData2, middleLen); */
    graph all =graph_cat(i->whiteGroup, i->blackGroup);
    printf("MIDDLEWAY\n");
    void* middleWay =graph_middleWay(i->reduceGraph, minWallGroup, all, minData, minData2, middleLen);
    graph_destroy(&all);
    plateau_searchPtrCasePos(i->p, middleWay, line, col);

    interface_placePawn(i, colorBotPawn, (unsigned)(*line), (unsigned)(*col));



    if (whiteSide1) {
        if (whiteSide1 ==1)
            printf("\x1B[32m");
        else
            printf("\x1B[31m");
        for (unsigned ind =0; ind <i->size; ind++) {
            printf("-");
        }
        printf("\x1B[0m");
        printf("\n");
    }
    for (int l =0; l <(int)i->size; l++) {
        if (blackSide1) {
            if (blackSide1 ==1)
                printf("\x1B[32m");
            else
                printf("\x1B[31m");
            printf("|");
            printf("\x1B[0m");
        }
        for (int c =0; c <(int)i->size; c++) {
            if (plateau_get(i->p, (unsigned)l, (unsigned)c)) {
                char car =(plateau_get(i->p, (unsigned)l, (unsigned)c) ==&i->whitePawn) ?('o') :('*');
                if (l ==minDataLine && c ==minDataColumn)
                    printf("\x1B[32m%c\x1B[0m", car);
                else if (l ==minData2Line && c ==minData2Column)
                    printf("\x1B[31m%c\x1B[0m", car);
                else if (l ==*line && c ==*col)
                    printf("\x1B[33m%c\x1B[0m", car);
                else
                    printf("%c", car);
            }
            else {
                printf(".");

            }

        }
        if (blackSide2) {
            if (blackSide2 ==1)
                printf("\x1B[32m");
            else
                printf("\x1B[31m");
            printf("|");
            printf("\x1B[0m");
        }
        printf("\n");
    }
    if (whiteSide2) {
        if (whiteSide2 ==1)
            printf("\x1B[32m");
        else
            printf("\x1B[31m");
        for (unsigned ind =0; ind <i->size; ind++) {
            printf("-");
        }
        printf("\x1B[0m");
        printf("\n");
    }
    printf("minLen =%d, middleLen =%d\n", minLen, middleLen);
    printf("onlyWhite =%d, onlyBlack =%d\n", cptOnlyWhite, cptOnlyBlack);
    printf("\n");
}

int interface_botTakePlace(interface i, int colorPawn) {
    int side =(int)i->size;
    int line;
    int column;
    int caseRemaining =side *side -(int)list_size(i->casePlayed);
    if (caseRemaining >10) {
        printf("Too leaf\n");

        /* do { */
        /*     line =rand() %side; */
        /*     column =rand() %side; */
        /* } while (interface_getPawn(i, (unsigned)line, (unsigned)column)); */

        /* interface_botBridge(i, colorPawn, &line, &column); */
        interface_botCutSmallerWay(i, colorPawn, &line, &column);
        /* interface_placePawn(i, colorPawn, (unsigned)line, (unsigned)column); */
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
        tree_widthBrowse(root, game_print);

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
            /* do { */
            /*     line =rand() %side; */
            /*     column =rand() %side; */
            /* } while (interface_getPawn(i, (unsigned)line, (unsigned)column)); */

            /* interface_placePawn(i, colorPawn, (unsigned)line, (unsigned)column); */
            /* interface_botBridge(i, colorPawn, &line, &column); */
            interface_botCutSmallerWay(i, colorPawn, &line, &column);
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


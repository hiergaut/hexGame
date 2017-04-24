#include "plateau.h"
#include <stdio.h>
#include "graph.h"
#include "sdl.h"
#include <math.h>
#include "ihm.h"
/* #include "SDL/SDL.h" */
/* #include <unistd.h> */
/* #include <wait.h> */
/* #include <stdlib.h> */

int main() {
    plateau p =plateau_create(5, 5);
    graph g =graph_create();
    sdl s =sdl_create();

    sdl_pictureFont(s, "./tableFont.jpg");

    ihm m =ihm_create(5);
    ihm_printPlateauOnly(m);
    /* unsigned tab[25]; */
    /* for (unsigned i =0 ;i <5 ;i++) { */
    /* 	for (unsigned j =0 ;j <5 ;j++) { */
    /* 		tab[i *5 +j] =i *5 +j; */
    /* 		plateau_insert(p, i, j, &tab[i *5 +j]); */
    /* 	} */
    /* } */
    /*  */
    /* #<{(| graph_insertVertex(g, &a); |)}># */
    /*  */
    /* void* square; */
    /* void* previous; */
    /* plateau_print(p); */
    /* for (unsigned i =0 ;i <5 ;i++) { */
    /* 	for (unsigned j =0 ;j <5 ;j++) { */
    /* 		previous =square; */
    /* 		square =plateau_get(p, i, j); */
    /* 		sdl_newObject(s, square); */
    /*  */
    /* 		if (i ==0 && j ==0) */
    /* 			sdl_setPosByOrigin(s, square, 50, 50); */
    /*  */
    /* 		else if (j ==0) */
    /* 			sdl_setPos(s, plateau_get(p, i -1, j), 0, 60, square); */
    /*  */
    /* 		else */
    /* 			sdl_setPos(s, previous, 60, 0, square); */
    /* 		 */
    /* 	} */
    /* } */
    /*  */
    /* for (unsigned i =0 ;i <5 ;i++) { */
    /* 	for (unsigned j =0 ;j <5 ;j++) { */
    /* 		graph_insertVertex(g, &tab[i *5 +j]); */
    /*  */
    /* 		previous =square; */
    /* 		square =plateau_get(p, i, j); */
    /* 		sdl_newObject(s, square); */
    /*  */
    /* 		if (i ==0 && j ==0) */
    /* 			sdl_setPosByOrigin(s, square, 650, 200); */
    /*  */
    /* 		else if (j ==0) */
    /* 			sdl_setPos(s, plateau_get(p, i -1, j), 50, 100, square); */
    /*  */
    /* 		else */
    /* 			sdl_setPos(s, previous, 100, 0, square); */
    /* 		 */
    /* 	} */
    /* } */
    /*  */
    /* int left =5; */
    /* int up =5; */
    /* int right; */
    /* int down; */
    /* sdl_newObject(s, &left); */
    /* sdl_newObject(s, &up); */
    /* sdl_newObject(s, &right); */
    /* sdl_newObject(s, &down); */
    /* sdl_setPos(s, plateau_get(p, 2, 0), -150, 0, &left); */
    /* sdl_setPos(s, plateau_get(p, 0, 2), 0, -150, &up); */
    /* sdl_setPos(s, plateau_get(p, 4, 2), 0, 150, &down); */
    /* sdl_setPos(s, plateau_get(p, 2, 4), 150, 0, &right); */
    /*  */
    /* void* cur; */
    /* for (unsigned i =0 ;i <5 ;i++) { */
    /* 	for (unsigned j =0 ;j <5 ;j++) { */
    /* 		cur =plateau_get(p, i, j); */
    /*  */
    /* 		if (j ==0) */
    /* 			sdl_link(s, cur, &left); */
    /* 		else */
    /* 			sdl_link(s, cur, plateau_get(p, i, j -1)); */
    /*  */
    /* 		if (i ==0) */
    /* 			sdl_link(s, cur, &up); */
    /* 		else */
    /* 			sdl_link(s, cur, plateau_get(p, i -1, j)); */
    /*  */
    /* 		if (i ==4) */
    /* 			sdl_link(s, cur, &down); */
    /* 		if (j ==4) */
    /* 			sdl_link(s, cur, &right); */
    /*  */
    /* 		if (i !=0 && j !=4) */
    /* 			sdl_link(s, cur, plateau_get(p, i -1, j +1)); */
    /*  */
    /* 	} */
    /* } */
    sdl_pause();
    /* graph_print(g); */

    /* int pid =fork(); */
    /* if (! pid) { */
    /* 	graph_print(g); */
    /* 	return 0; */
    /* } */
    /* system("sleep 1"); */
    /* pid =fork(); */
    /* if (! pid) { */
    /* 	graph_print(g); */
    /* 	return 0; */
    /* } */
    /*  */
    /* wait(NULL); */
    /* wait(NULL); */

    plateau_destroy(&p);
    graph_destroy(&g);
    sdl_destroy(&s);


    return 0;
}

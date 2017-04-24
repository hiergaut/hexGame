#include <math.h>
#include "sdl.h"
#include "ihm.h"



ihm ihm_create(int size) {
    ihm born;
    born.plateauSize =size;
    born.top.x =900;
    born.top.y =200;
    born.caseHeight =80;
    born.caseSide =(int)(born.caseHeight /sqrt(3));

    born.s =sdl_create();

    return born;
}

void ihm_destroy(ihm ih) {
    sdl_destroy(&ih.s);
}
    

pos ihm_casePos(ihm m, int i, int j) {
    pos p;
    p.x =m.top.x +(3 *m.caseSide *(j -i)) /2;
    p.y =m.top.y +(m.caseHeight *(i +j)) /2;

    return p;
}

void ihm_printPlateauOnly(ihm m) {
    pos p;
    for (int i =0 ;i <m.plateauSize ;i++) {
	for (int j =0 ;j <m.plateauSize ;j++) {
	    p =ihm_casePos(m, j, i);
	    sdl_hexagone(sdl_getScreen(), p.x, p.y, m.caseHeight);
	    /* sdl_floodfill(sdl_getScreen(), p.x, p.y, sdl_color(211, 181, 129), SDL_BLACK); */
	    sdl_floodfill(sdl_getScreen(), p.x, p.y, sdl_color(211, 181, 129), SDL_BLACK);
	}
    }

    p =ihm_casePos(m, 0, 0);
    pos p2 =ihm_casePos(m, m.plateauSize -1, 0);
    pos p3 =ihm_casePos(m, m.plateauSize -1, m.plateauSize -1);
    pos p4 =ihm_casePos(m, 0, m.plateauSize -1);

    int marge =20;
    sdl_line(sdl_getScreen(), p.x, 
	    p.y -m.caseHeight /2 -(int)(m.caseSide /(2 *sqrt(3))) -(int)(marge /sqrt(3)), 
	    p2.x -(m.caseSide) *2 -marge, p2.y);
    sdl_line(sdl_getScreen(), p.x, 
	    p.y -m.caseHeight /2 -(int)(m.caseSide /(2 *sqrt(3))) -(int)(marge /sqrt(3)), 
	    p4.x +(m.caseSide) *2 +marge, p4.y);
    sdl_line(sdl_getScreen(), p3.x, 
	    p3.y +m.caseHeight /2 +(int)(m.caseSide /(2 *sqrt(3))) +(int)(marge /sqrt(3)), 
	    p4.x +(m.caseSide) *2 +marge, p4.y);
    sdl_line(sdl_getScreen(), p3.x, 
	    p3.y +m.caseHeight /2 +(int)(m.caseSide /(2 *sqrt(3))) +(int)(marge /sqrt(3)), 
	    p2.x -(m.caseSide) *2 -marge, p2.y);

    sdl_line(sdl_getScreen(), p.x, p.y -m.caseHeight /2, 
	    p.x, p.y -m.caseHeight /2 -(int)(m.caseSide /(2 *sqrt(3))) -(int)(marge /sqrt(3))); 
    sdl_line(sdl_getScreen(), p3.x, p3.y +m.caseHeight /2, 
	    p3.x, p3.y +m.caseHeight /2 +(int)(m.caseSide /(2 *sqrt(3))) +(int)(marge /sqrt(3))); 
    sdl_line(sdl_getScreen(), p2.x -(m.caseSide), p2.y, 
	    p2.x -(m.caseSide) *2 -marge, p2.y);
    sdl_line(sdl_getScreen(), p4.x +(m.caseSide), p4.y, 
	    p4.x +(m.caseSide) *2 +marge, p4.y);


    sdl_floodfill(sdl_getScreen(), p.x +1, p.y -m.caseHeight /2 -1, SDL_BLACK, SDL_BLACK);
    sdl_floodfill(sdl_getScreen(), p.x -1, p.y -m.caseHeight /2 -1, SDL_WHITE, SDL_BLACK);
    sdl_floodfill(sdl_getScreen(), p3.x +1, p3.y +m.caseHeight /2 +1, SDL_WHITE, SDL_BLACK);
    sdl_floodfill(sdl_getScreen(), p3.x -1, p3.y +m.caseHeight /2 +1, SDL_BLACK, SDL_BLACK);
    SDL_Flip(screen);

}

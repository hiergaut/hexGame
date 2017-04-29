#include "sdl.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "list.h"
#include <time.h>
#include <math.h>
/* #include <SDL/SDL_types.h> */
#include <SDL/SDL_image.h>
/* #include <SDL2/SDL.h> */
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
/* #define SCREEN_FONT_COLOR 0xA0, 0xA0, 0xA0 */
#define SCREEN_FONT_COLOR 241, 219, 170

#define OBJ_WIDTH 50
#define OBJ_HEIGHT 50

#define FONT_RED 0xA0
#define FONT_GREEN 0xA0
#define FONT_BLUE 0xA0

TTF_Font *police =NULL;

void sdl_create(int width, int height, const char* str) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    /* TTF_Init(); */
    SDL_WM_SetCaption(str, NULL);


    screen =SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
    police =TTF_OpenFont("Roboto-Regular.ttf", 20);
    /* TTF_SetFontStyle(police, TTF_STYLE_UNDERLINE); */
    /* screen =SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE| SDL_FULLSCREEN); */
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, SCREEN_FONT_COLOR));
    SDL_Flip(screen);
}

void sdl_quit() {
    TTF_CloseFont(police);
    TTF_Quit();
    /* SDL_VideoQuit(); */
    SDL_Quit();
}

SDL_Surface* sdl_newSurface(int width, int height, int x, int y, const char* str) {
    SDL_Surface* su =SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0, 0, 0 ,0);
    SDL_FillRect(su, NULL, SDL_WHITE); 
    /* SDL_Rect pos; */
    /* pos.x =(short)x; */
    /* pos.y =(short)y; */
    /* SDL_SetClipRect(su, &pos); */
    su->clip_rect.x =(short)x;
    su->clip_rect.y =(short)y;
    /* sdl_rectangle(screen, x -1 , y -1, x +su->w +1, y +su->h +1, SDL_BLACK); */
    SDL_BlitSurface(su, NULL, screen, &su->clip_rect);

    SDL_Surface* text;
    SDL_Color blackColor ={0, 0, 0, 0};
    text = TTF_RenderText_Blended(police, str, blackColor);
    SDL_Rect pos;
    pos.y =(short)(y -25);
    pos.x =(short)(x +su->w /2 -text->w /2);
    SDL_BlitSurface(text, NULL, screen, &pos);
    SDL_FreeSurface(text);

    SDL_Flip(screen);
    return su;
}

SDL_Surface* sdl_getScreen() {
    return screen;
}

void sdl_clean(SDL_Surface* area, Uint32 color) {
    Uint32* pixel =(Uint32*)(area->pixels);
    for (int l =0; l <area->h; l++) {
        for (int c =0; c< area->w; c++) {
            *(pixel +l *area->w +c) =color;
        }
    }
    /* SDL_FillRect(area, NULL, SDL_WHITE); */
    /* SDL_BlitSurface(area, NULL, screen, &area->clip_rect); */
    /* SDL_Flip(screen); */
}


void sdl_pictureFont(SDL_Surface* area, const char* file) {
    SDL_Surface* font = IMG_Load(file);
    SDL_Rect pos;
    pos.x =0;
    pos.y =0;
    SDL_BlitSurface(font, NULL, area, &pos);
}

void genPos(SDL_Rect* pos) {
    pos->x =(short)(rand() %(SCREEN_WIDTH -OBJ_WIDTH));
    pos->y =(short)(rand() %(SCREEN_HEIGHT -OBJ_HEIGHT));
}


void sdl_pause() {
    int continuer = 1;
    SDL_Event event;
    while (continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym ==SDLK_q)
                    continuer =0;
                break;
            default:
                break;
        }
    }
}

void putpixel(SDL_Surface* area, int xe, int ye, Uint32 c) { 
    Uint32 * numerocase; 
    numerocase= (Uint32 *)(area->pixels)+xe+ye*area->w;    
    *numerocase=c; 
} 

Uint32 getpixel(SDL_Surface* area, int xe, int ye) { 
    Uint32 * numerocase; 
    numerocase= (Uint32 *)(area->pixels)+xe+ye*area->w;   
    return (*numerocase); 
} 

void sdl_lineSimple(SDL_Surface* area, int x0,int y0, int x1,int y1, Uint32 c) { 
    int dx,dy,x,y,residu,absdx,absdy,stepx,stepy,i; 
    dx=x1-x0; 
    dy=y1-y0;  
    residu=0;       
    x=x0;
    y=y0;  
    putpixel(area, x,y,c); 
    if (dx>0) 
        stepx=1;
    else 
        stepx=-1; 
    if (dy>0) 
        stepy=1;
    else 
        stepy=-1; 
    absdx=abs(dx);
    absdy=abs(dy); 
    if (dx==0) 
        for(i=0;i<absdy;i++) { 
            y+=stepy; 
            putpixel(area, x,y,c); 
        } 
    else if (dy==0) 
        for(i=0;i<absdx;i++) { 
            x+=stepx; 
            putpixel(area, x,y,c);  
        } 
    else if (absdx==absdy) 
        for( i=0;i<absdx;i++) {
            x+=stepx; 
            y+=stepy; 
            putpixel(area, x,y,c); 
        } 
    else if (absdx>absdy) 
        for(i=0;i<absdx;i++) { 
            x+=stepx; residu+=absdy; 
            if(residu >= absdx) {
                residu -=absdx; 
                y+=stepy;
            } 
            putpixel(area, x,y,c); 
        } 
    else for (i=0;i<absdy;i++) {
        y+=stepy; 
        residu +=absdx; 
        if (residu>=absdy)   {
            residu -= absdy;x +=stepx;
        } 
        putpixel(area, x,y,c); 
    } 
} 

void line(SDL_Surface* area, int x0,int y0, int x1,int y1, Uint32 c) { 
    int dx,dy,x,y,residu,absdx,absdy,pasx,pasy,i; 
    dx=x1-x0; 
    dy=y1-y0;  
    residu=0;       
    x=x0;
    y=y0;  
    if (x>=0 && x<area->w && y>=0 && y<area->h) 
        putpixel(area, x,y,c); 
    if (dx>0) 
        pasx=1;
    else 
        pasx=-1; 
    if (dy>0) 
        pasy=1; 
    else 
        pasy=-1; 
    absdx=abs(dx);
    absdy=abs(dy); 
    if (dx==0) 
        for(i=0;i<absdy;i++) { 
            y+=pasy; 
            if (x>=0 && x<area->w && y>=0 && y<area->h) 
                putpixel(area, x,y,c);
        } 
    else if(dy==0) 
        for(i=0;i<absdx;i++){ 
            x+=pasx; 
            if (x>=0 && x<area->w && y>=0 && y<area->h) 
                putpixel(area, x,y,c);  
        } 
    else if (absdx==absdy) 
        for(i=0;i<absdx;i++) {
            x+=pasx; 
            if (x>=0 && x<area->w && y>=0 && y<area->h) 
                putpixel(area, x,y,c); 
            y+=pasy; 
            if (x>=0 && x<area->w && y>=0 && y<area->h) 
                putpixel(area, x,y,c); 
        } 
    else if (absdx>absdy) 
        for(i=0;i<absdx;i++) { 
            x+=pasx; 
            if (x>=0 && x<area->w && y>=0 && y<area->h)
                putpixel(area, x,y,c); 
            residu+=absdy; 
            if(residu >= absdx) {
                residu -=absdx; y+=pasy; 
                if (x>=0 && x<area->w && y>=0 && y<area->h) 
                    putpixel(area, x,y,c); 
            } 
        } 
    else 
        for(i=0;i<absdy;i++) {
            y+=pasy; 
            if (x>=0 && x<area->w && y>=0 && y<area->h) 
                putpixel(area, x,y,c); 
            residu +=absdx; 
            if (residu>=absdy) {
                residu -= absdy;
                x +=pasx; 
                if (x >=0 && x<area->w && y>=0 && y<area->h) 
                    putpixel(area, x,y,c); 
            } 
        } 
} 

void sdl_line(SDL_Surface* area, int x, int y, int x2, int y2) {
    line(area, x, y, x2, y2, SDL_BLACK);
    /* lineScale(area, x, y, x2, y2, SDL_BLACK); */
    SDL_Flip(screen);
}


void linewithwidth(SDL_Surface* area, int x1, int y1, int x2, int y2, 
        int width,Uint32 c) { 
	int dx,dy; 
    double k,xf1,yf1,xf2,yf2,d,dx1,dy1,ndx1,ndy1,ndx2,ndy2,angle=M_PI/2.; 
    line(area, (int)x1,(int)y1,(int)x2,(int)y2,c); 
    dx=x2-x1; 
    dy=y2-y1;       
    d=sqrt(dx*dx+dy*dy); 
    if ((int)d!=0) { 
        dx1=(double)width*(double)dx/d; 
        dy1=(double)width*(double)dy/d; 
        ndx1=dx1*cos(angle)-dy1*sin(angle); 
        ndy1=dx1*sin(angle)+dy1*cos(angle); 
        ndx2=dx1*cos(-angle)-dy1*sin(-angle); 
        ndy2=dx1*sin(-angle)+dy1*cos(-angle); 
        for(k=0;k<=1.;k+=0.1/d) 
        { 
            xf1=(1.-k)*x1+k*x2; yf1=(1.-k)*y1+k*y2; 
            xf2=xf1-ndx1; yf2=yf1-ndy1;  
            line(area, (int)xf1,(int)yf1,(int)xf2,(int)yf2,c); 
            xf2=xf1-ndx2; yf2=yf1-ndy2;    
            line(area, (int)xf1,(int)yf1,(int)xf2,(int)yf2,c); 
        } 
    } 
} 

void sdl_hexagone(SDL_Surface* area, int x, int y, int h) {
    int c =(int)(h /sqrt(3));

    int r =x +c /2;
    int l =x -c /2;
    int u =y -(h /2);
    int d =y +(h /2);

    line(area, l, u, r, u, SDL_BLACK);
    line(area, r, u, x +c, y, SDL_BLACK);
    line(area, x +c, y, r, d, SDL_BLACK);
    line(area, r, d, l, d, SDL_BLACK);
    line(area, l, d, x -c, y, SDL_BLACK);
    line(area, x -c, y, l, u, SDL_BLACK);

    SDL_Flip(screen);
}


void sdl_floodfill(SDL_Surface* area, int x, int y, Uint32 cr, Uint32 cb) {   
    int xg,xd,xx; 
    if (getpixel(area, x,y) !=cb && getpixel(area, x,y) !=cr) { 
        putpixel(area, x,y,cr); 
        xg=x-1; 
        while(xg>0 && getpixel(area, xg,y)!=cb) {
            putpixel(area, xg, y,cr); 
            xg--;
        } 
        xd=x+1; 
        while(xd<area->w && getpixel(area, xd,y)!=cb) {
            putpixel(area, xd,y,cr); 
            xd++ ;
        } 
        for(xx=xg; xx<xd;xx++) { 
            if (y>1 ) {
                sdl_floodfill(area, xx,y-1,cr,cb);
            } 
            if (y<area->h -1 ) {
                sdl_floodfill(area, xx,y+1,cr,cb);
            } 
        } 
    } 
} 

Uint32 sdl_color(unsigned char r, unsigned char g, unsigned char b) {
    return SDL_MapRGB(screen->format, r, g, b);
}

void sdl_rectangle(SDL_Surface* area, int x1,int y1, int x2, int y2, Uint32 c) { 
    line(area, x1,y1,x2,y1,c);
    line(area, x1,y2,x2,y2,c);
    line(area, x1,y1,x1,y2,c);
    line(area, x2,y2,x2,y1,c); 
} 

void sdl_square(SDL_Surface* area, int x, int y, int side, Uint32 c) {
    sdl_rectangle(area, x, y, x +side, y +side, c);
}

void sdl_squareFill(SDL_Surface* area, int x, int y, int side, Uint32 c, Uint32 fill) {
    sdl_square(area, x, y, side, c);
    sdl_floodfill(area, x +1, y +1, fill, c);
}

Uint32 sdl_uniqColorData(void* data) {
    /* int key =data; */
    long key =(long)data %10000;
    /* printf("data =%p\n", data); */
    /* printf("key =%ld\n" ,key); */

    unsigned char r;
    unsigned char g;
    unsigned char b;

    r =(unsigned char)(key *13);
    g =(unsigned char)(key *47);
    b =(unsigned char)(key *97);

    return SDL_MapRGB(screen->format, r, g, b);
}

void sdl_circle(SDL_Surface* area, int xo, int yo, int R, Uint32 c) { 
    int x, y, F, F1, F2,newx,newy; 
    x=xo; 
    y=yo+R; 
    F=0; 
    if (x<area->w && x>=0 && y>=0 && y<area->h) 
        putpixel(area, x,y,c); 
    if (x<area->w && x>=0 && 2*yo-y>=0 && 2*yo-y<area->h)
        putpixel (area, x,2*yo-y, c); 
    while( y>yo) 
    { 
        F1=F+2*(x-xo)+1; 
        F2=F-2*(y-yo)+1; 
        if ( abs(F1)<abs(F2)) { 
            x+=1; F=F1;
        } 
        else {
            y-=1; 
            F=F2;
        } 
        if (x<area->w && x>=0 && y>=0 && y<area->h) 
            putpixel(area, x,y,c); 

        newx=2*xo-x ; newy=2*yo-y ; 
        if (x<area->w && x>=0 && newy>=0 && newy<area->h) 
            putpixel(area, x, newy,c); 
        if (newx<area->w && newx>=0 && y>=0 && y<area->h) 
            putpixel(area, newx,y,c); 
        if (newx<area->w && newx>=0 && newy>=0 && newy<area->h) 
            putpixel(area, newx, newy, c); 
    } 
    if (xo+R<area->w && xo+R>=0) 
        putpixel(area, xo+R,yo,c); 
    if (xo-R<area->w && xo-R>=0) 
        putpixel(area, xo-R,yo, c); 
} 

void sdl_disk(SDL_Surface* area, int x, int y, int r, Uint32 c) {
    sdl_circle(area, x, y, r, c);
    sdl_floodfill(area, x, y, c, c);
}



/* void majMiddlePos(object o) { */
/*     o->middlePos.x =(short)(o->pos.x +OBJ_WIDTH /2); */
/*     o->middlePos.y =(short)(o->pos.y +OBJ_HEIGHT /2); */
/* } */
/*  */
/* object object_create(const void* data) { */
/*     object o =malloc(sizeof(struct s_object)); */
/*  */
/*     o->area =SDL_CreateRGBSurface(SDL_HWSURFACE, OBJ_WIDTH, OBJ_HEIGHT, 32, 0, 0, 0, 0); */
/*     genPos(&o->pos); */
/*     o->data =data; */
/*     majMiddlePos(o); */
/*  */
/*     int key =*(const int*)data; */
/*     key =(int)pow(key, 2) %256; */
/*     unsigned char key2 =(unsigned char)key; */
/*     key =(int)pow(key, 3) %256; */
/*     unsigned char key3 =(unsigned char)key; */
/*     key =(int)pow(key, 4) %256; */
/*     unsigned char key4 =(unsigned char)key; */
/*     #<{(| printf("%d %d %d\n", key2, key3, key4); |)}># */
/*  */
/*     SDL_FillRect(o->area, NULL, SDL_MapRGB(screen->format, key2, key3, key4)); */
/*     #<{(| SDL_BlitSurface(o->area, NULL, screen, &o->pos); |)}># */
/*  */
/*  */
/*     #<{(| char str[30]; |)}># */
/*     #<{(| sprintf(str, "%p", o->data); |)}># */
/*     #<{(| SDL_Color black ={FONT_RED, FONT_GREEN, FONT_BLUE, 0}; |)}># */
/*     #<{(| o->text =TTF_RenderText_Blended(s->police, str, black); |)}># */
/*     #<{(| SDL_BlitSurface(o->text, NULL, s->screen, &o->pos); |)}># */
/*  */
/*     SDL_Flip(screen); */
/*     return o; */
/* } */

/* #<{(|  |)}># */
/* void object_destroy(object* o) { */
/*     SDL_FreeSurface((*o)->area); */
/*     free(*o); */
/*     *o =NULL; */
/* } */


/* object search(sdl s, void* data) { */
/*     list_it it =list_it_create(s->object); */
/*     object o; */
/*     while (! list_it_end(it)) { */
/* 	o =list_it_get(it); */
/* 	if (o->data ==data) { */
/* 	    list_it_destroy(&it); */
/* 	    return o; */
/* 	} */
/*  */
/* 	list_it_next(it); */
/*     } */
/*     list_it_destroy(&it); */
/*     return NULL; */
/* } */

/* void sdl_link(sdl s, void* data, void* data2) { */
/*     object o =search(s, data); */
/*     object o2 =search(s, data2); */
/*  */
/*     line(screen, o->middlePos.x, o->middlePos.y, o2->middlePos.x, o2->middlePos.y, SDL_BLACK); */
/*     SDL_BlitSurface(o->area, NULL, screen, &o->pos); */
/*     SDL_BlitSurface(o2->area, NULL, screen, &o2->pos); */
/*     SDL_Flip(screen); */
/* } */
/*  */
/* void sdl_setPos(sdl s, void* data, int dx, int dy, void* data2) { */
/*     object o =search(s, data); */
/*     object o2 =search(s, data2); */
/*  */
/*     o2->pos.x =(short)(o->pos.x +dx); */
/*     o2->pos.y =(short)(o->pos.y +dy); */
/*     majMiddlePos(o2); */
/*     SDL_BlitSurface(o2->area, NULL, screen, &o2->pos); */
/*     SDL_Flip(screen); */
/* } */
/*  */
/* void sdl_setPosByOrigin(sdl s, void* data, int dx, int dy) { */
/*     object o =search(s, data); */
/*  */
/*     o->pos.x =(short)(dx); */
/*     o->pos.y =(short)(dy); */
/*     majMiddlePos(o); */
/*     SDL_BlitSurface(o->area, NULL, screen, &o->pos); */
/*     SDL_Flip(screen); */
/* } */


/* void pause(void)  */
/* {  */
/*     SDL_Event evenement;  */
/*     do   SDL_WaitEvent(&evenement);  */
/*     while(evenement.type != SDL_QUIT && evenement.type != SDL_KEYDOWN);  */
/* }  */
/*  */
/* void filldisc( int xo, int yo, int R, Uint32 c)  */
/* {  */
/* 	int x, y, F, F1, F2,newx,newy,xx;  */
/* 	x=xo; y=yo+R; F=0;  */
/* 	if (x<800 && x>=0 && y>=0 && y<600) putpixel( */
/* 			x,y,c);  */
/* 	if (x<800 && x>=0 && 2*yo-y>=0 && 2*yo-y<600) */
/* 		putpixel (x,2*yo-y, c);  */
/* 	while( y>yo)  */
/* 	{  */
/* 		F1=F+2*(x-xo)+1; F2=F-2*(y-yo)+1;  */
/* 		if ( abs(F1)<abs(F2))  { x+=1; F=F1;}  */
/* 		else {y-=1; F=F2;}  */
/* 		newx=2*xo-x ; newy=2*yo-y ;  */
/* 		for(xx=newx; xx<=x; xx++)if (xx<800 && */
/* 				xx>=0 && y>=0 && y<600 )  */
/* 			putpixel(xx,y,c);  */
/* 		for(xx=newx; xx<=x; xx++)if (xx<800 && */
/* 				xx>=0 && newy>=0 && newy<600 )  */
/* 			putpixel(xx,newy,c);  */
/* 	}  */
/* 	if (xo+R<800 && xo+R>=0&& y>=0 && y<600) put */
/* 		pixel(xo+R,yo,c);  */
/* 	if (xo-R<800 && xo-R>=0&& y>=0 && y<600) put */
/* 		pixel(xo-R,yo, c);  */
/* }  */
/* void arrow(int x1, int y1, int x2, int y2, Uint32 c */
/* 		)  */
/* {  */
/* 	int dx,dy;  */
/* 	float xf1,yf1,xf2,yf2,d,dx1,dy1,ndx1,ndy1,ndx2,ndy2 */
/* 		,angle=M_PI/6.;  */
/* 	line(x1,y1,x2,y2,c);  */
/* 	dx=x2-x1; dy=y2-y1;       d=sqrt(dx*dx+dy*dy);  */
/* 	if (d!=0.)  */
/* 	{ dx1=6.*(float)dx/d; dy1=6.*(float)dy/d;  */
/* 		ndx1=dx1*cos(angle)-dy1*sin(angle);  */
/* 		ndy1=dx1*sin(angle)+dy1*cos(angle);  */
/* 		4  */
/* 			xf1=0.3*x1+0.7*x2; yf1=0.3*y1+0.7*y2;     xf2=xf */
/* 			1-ndx1; yf2=yf1-ndy1;  */
/* 		line(xf1,yf1,xf2,yf2,c);  */
/* 		ndx2=dx1*cos(-angle)-dy1*sin(-angle);  */
/* 		ndy2=dx1*sin(-angle)+dy1*cos(-angle);  */
/* 		xf2=xf1-ndx2; yf2=yf1-ndy2;    line(xf1,yf1,xf2, */
/* 				yf2,c);  */
/* 	}  */
/* 	else  */
/* 	{circle(x1+10,y1,10,c); line(x1+20,y1,x1+23,y1 */
/* 			-6,c);  */
/* 	line(x1+20,y1,x1+15,y1-5,c);  */
/* 	}  */
/* }  */
/** 
  add  #include <math.h> 
  */ 
/* void arc0_90( int xo, int yo, int R, Uint32 c)  */
/* {  */
/* 	int x, y, F, F1, F2,newx,newy;  */
/* 	x=xo; y=yo+R; F=0;  */
/* 	if (x<800 && x>=0 && 2*yo-y>=0 && 2*yo-y<600) */
/* 		putpixel (x,2*yo-y, c);  */
/* 	while( y>yo)  */
/* 	{  */
/* 		F1=F+2*(x-xo)+1; F2=F-2*(y-yo)+1;  */
/* 		if ( abs(F1)<abs(F2))  { x+=1; F=F1;}  */
/* 		else {y-=1; F=F2;}  */
/* 		5  */
/* 			newy=2*yo-y ;  */
/* 		if (x<800 && x>=0 && newy>=0 && newy<6 */
/* 				00) putpixel(x, newy,c);  */
/* 	}  */
/* 	if (xo+R<800 && xo+R>=0) putpixel(xo+R,yo,c) */
/* 		;  */
/* }  */
/* void arc270_360( int xo, int yo, int R, Uint32 c) */
/* {  */
/* 	int x, y, F, F1, F2,newx,newy;  */
/* 	x=xo; y=yo+R; F=0;  */
/* 	if (x<800 && x>=0 && y>=0 && y<600) putpixel( */
/* 			x,y,c);  */
/* 	while( y>yo)  */
/* 	{  */
/* 		F1=F+2*(x-xo)+1; F2=F-2*(y-yo)+1;  */
/* 		if ( abs(F1)<abs(F2))  { x+=1; F=F1;}  */
/* 		else {y-=1; F=F2;}  */
/* 		if (x<800 && x>=0 && y>=0 && y<600) pu */
/* 			tpixel(x,y,c);  */
/* 	}  */
/* 	if (xo+R<800 && xo+R>=0) putpixel(xo+R,yo,c) */
/* 		;  */
/* }  */
/* void arc90_180( int xo, int yo, int R, Uint32 c)  */
/* {  */
/* 	int x, y, F, F1, F2,newx,newy;  */
/* 	x=xo; y=yo+R; F=0;  */
/* 	if (x<800 && x>=0 && 2*yo-y>=0 && 2*yo-y<600) */
/* 		putpixel (x,2*yo-y, c);  */
/* 	while( y>yo)  */
/* 	{  */
/* 		F1=F+2*(x-xo)+1; F2=F-2*(y-yo)+1;  */
/* 		if ( abs(F1)<abs(F2))  { x+=1; F=F1;}  */
/* 		else {y-=1; F=F2;}  */
/* 		newx=2*xo-x ; newy=2*yo-y ;  */
/* 		if (newx<800 && newx>=0 && newy>=0 &&  */
/* 				newy<600) putpixel(newx,  */
/* 					newy, c);  */
/* 	}  */
/* 	if (xo-R<800 && xo-R>=0) putpixel(xo-R,yo, c */
/* 			);  */
/* }  */
/* void arc180_270( int xo, int yo, int R, Uint32 c)  */
/* {  */
/* 	int x, y, F, F1, F2,newx,newy;  */
/* 	x=xo; y=yo+R; F=0;  */
/* 	if (x<800 && x>=0 && y>=0 && y<600) putpixel( */
/* 			x,y,c);  */
/* 	while( y>yo)  */
/* 	{  */
/* 		F1=F+2*(x-xo)+1; F2=F-2*(y-yo)+1;  */
/* 		if ( abs(F1)<abs(F2))  { x+=1; F=F1;}  */
/* 		else {y-=1; F=F2;}  */
/* 		newx=2*xo-x ;  */
/* 		if (newx<800 && newx>=0 && y>=0 && y<6 */
/* 				00) putpixel( newx,y,c);  */
/* 	}  */
/* 	if (xo-R<800 && xo-R>=0) putpixel(xo-R,yo, c */
/* 			);  */
/* }  */
/* void arc0_180( int xo, int yo, int R, Uint32 c)  */
/* 	6  */
/* {  */
/* 	int x, y, F, F1, F2,newx,newy;  */
/* 	x=xo; y=yo+R; F=0;  */
/* 	if (x<800 && x>=0 && 2*yo-y>=0 && 2*yo-y<600) */
/* 		putpixel (x,2*yo-y, c);  */
/* 	while( y>yo)  */
/* 	{  */
/* 		F1=F+2*(x-xo)+1; F2=F-2*(y-yo)+1;  */
/* 		if ( abs(F1)<abs(F2))  { x+=1; F=F1;}  */
/* 		else {y-=1; F=F2;}  */
/* 		newx=2*xo-x ; newy=2*yo-y ;  */
/* 		if (x<800 && x>=0 && newy>=0 && newy<6 */
/* 				00) putpixel(x, newy,c);  */
/* 		if (newx<800 && newx>=0 && newy>=0 &&  */
/* 				newy<600) putpixel(newx,  */
/* 					newy, c);  */
/* 	}  */
/* 	if (xo+R<800 && xo+R>=0) putpixel(xo+R,yo,c) */
/* 		;  */
/* 	if (xo-R<800 && xo-R>=0) putpixel(xo-R,yo, c */
/* 			);  */
/* }  */
/* void arc180_360( int xo, int yo, int R, Uint32 c) */
/* {  */
/* 	int x, y, F, F1, F2,newx,newy;  */
/* 	x=xo; y=yo+R; F=0;  */
/* 	if (x<800 && x>=0 && y>=0 && y<600) putpixel( */
/* 			x,y,c);  */
/* 	while( y>yo)  */
/* 	{  */
/* 		F1=F+2*(x-xo)+1; F2=F-2*(y-yo)+1;  */
/* 		if ( abs(F1)<abs(F2))  { x+=1; F=F1;}  */
/* 		else {y-=1; F=F2;}  */
/* 		if (x<800 && x>=0 && y>=0 && y<600) pu */
/* 			tpixel(x,y,c);  */
/* 		newx=2*xo-x ;  */
/* 		if (newx<800 && newx>=0 && y>=0 && y<6 */
/* 				00) putpixel( newx,y,c);  */
/* 	}  */
/* 	if (xo-R<800 && xo-R>=0) putpixel(xo-R,yo, c */
/* 			);  */
/* }  */
/* void arc270_90( int xo, int yo, int R, Uint32 c)  */
/* {  */
/* 	int x, y, F, F1, F2,newx,newy;  */
/* 	x=xo; y=yo+R; F=0;  */
/* 	if (x<800 && x>=0 && y>=0 && y<600) putpixel( */
/* 			x,y,c);  */
/* 	if (x<800 && x>=0 && 2*yo-y>=0 && 2*yo-y<600) */
/* 		putpixel (x,2*yo-y, c);  */
/* 	while( y>yo)  */
/* 	{  */
/* 		F1=F+2*(x-xo)+1; F2=F-2*(y-yo)+1;  */
/* 		if ( abs(F1)<abs(F2))  { x+=1; F=F1;}  */
/* 		else {y-=1; F=F2;}  */
/* 		if (x<800 && x>=0 && y>=0 && y<600) pu */
/* 			tpixel(x,y,c);  */
/* 		newy=2*yo-y ;  */
/* 		if (x<800 && x>=0 && newy>=0 && newy<6 */
/* 				00) putpixel(x, newy,c);  */
/* 	}  */
/* 	if (xo+R<800 && xo+R>=0) putpixel(xo+R,yo,c) */
/* 		;  */
/* }  */
/* 	7  */
/* void arc90_270( int xo, int yo, int R, Uint32 c)  */
/* {  */
/* 	int x, y, F, F1, F2,newx,newy;  */
/* 	x=xo; y=yo+R; F=0;  */
/* 	if (x<800 && x>=0 && y>=0 && y<600) putpixel( */
/* 			x,y,c);  */
/* 	if (x<800 && x>=0 && 2*yo-y>=0 && 2*yo-y<600) */
/* 		putpixel (x,2*yo-y, c);  */
/* 	while( y>yo)  */
/* 	{  */
/* 		F1=F+2*(x-xo)+1; F2=F-2*(y-yo)+1;  */
/* 		if ( abs(F1)<abs(F2))  { x+=1; F=F1;}  */
/* 		else {y-=1; F=F2;}  */
/* 		newx=2*xo-x ; newy=2*yo-y ;  */
/* 		if (newx<800 && newx>=0 && y>=0 && y<6 */
/* 				00) putpixel( newx,y,c);  */
/* 		if (newx<800 && newx>=0 && newy>=0 &&  */
/* 				newy<600) putpixel(newx,  */
/* 					newy, c);  */
/* 	}  */
/* 	if (xo-R<800 && xo-R>=0) putpixel(xo-R,yo, c */
/* 			);  */
/* }  */

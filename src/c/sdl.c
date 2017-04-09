#include "sdl.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "list.h"
#include <time.h>
/* #include <SDL/SDL_types.h> */
/* #include <SDL/SDL_image.h> */

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define OBJ_WIDTH 50
#define OBJ_HEIGHT 50

#define FONT_RED 0xA0
#define FONT_GREEN 0xA0
#define FONT_BLUE 0xA0

struct s_sdl {
	SDL_Surface* screen;
	list object;
	TTF_Font* police;
};

struct s_object {
	SDL_Surface* area;
	SDL_Rect pos;
	const void* data;
	SDL_Surface* text;
};
typedef struct s_object* object;

sdl sdl_create() {
	srand((unsigned)time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_WM_SetCaption("HexGame : Graphe" ,NULL);


	sdl s =malloc(sizeof(struct s_sdl));
	s->object =list_create();
	s->police =TTF_OpenFont("font.ttf" ,20);

	s->screen =SDL_SetVideoMode(SCREEN_WIDTH ,SCREEN_HEIGHT ,32 ,SDL_HWSURFACE);
	SDL_FillRect(s->screen ,NULL ,SDL_MapRGB(s->screen->format ,FONT_RED ,FONT_GREEN ,FONT_BLUE));
	SDL_Flip(s->screen);

	return s;
}

void genPos(SDL_Rect* pos) {
	pos->x =(short)(rand() %(SCREEN_WIDTH -OBJ_WIDTH));
	pos->y =(short)(rand() %(SCREEN_HEIGHT -OBJ_HEIGHT));
}

object object_create(sdl s ,const void* data) {
	object o =malloc(sizeof(struct s_object));

	o->area =SDL_CreateRGBSurface(SDL_HWSURFACE ,OBJ_WIDTH ,OBJ_HEIGHT ,32 ,0 ,0 ,0 ,0);
	genPos(&o->pos);
	o->data =data;

	int key =*(const int*)data;
	unsigned char key2 =(unsigned char)key;
	key =key *key;
	unsigned char key3 =(unsigned char)key;
	key =key *key;
	unsigned char key4 =(unsigned char)key;
	/* printf("%d %d %d\n" ,key2 ,key3 ,key4); */

	SDL_FillRect(o->area ,NULL ,SDL_MapRGB(s->screen->format ,key2 ,key3 ,key4));
	SDL_BlitSurface(o->area ,NULL ,s->screen ,&o->pos);


	/* char str[30]; */
	/* sprintf(str ,"%p" ,o->data); */
	/* SDL_Color black ={FONT_RED ,FONT_GREEN ,FONT_BLUE ,0}; */
	/* o->text =TTF_RenderText_Blended(s->police ,str ,black); */
	/* SDL_BlitSurface(o->text ,NULL ,s->screen ,&o->pos); */

	SDL_Flip(s->screen);
	return o;
}

void object_destroy(object* o) {
	SDL_FreeSurface((*o)->area);
	free(*o);
	*o =NULL;
}

void sdl_destroy(sdl* s) {
	list l =((*s)->object);
	object o;
	while (! list_empty(l)) {
		o =list_back(l);
		object_destroy(&o);
		list_popBack(l);
	}

	TTF_Quit();
	SDL_VideoQuit();
	SDL_Quit();

	free(*s);
	*s =NULL;
}


void sdl_pause() {
	int continuer = 1;
	SDL_Event event;
	while (continuer) {
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT:
				continuer = 0;
			default:
				break;
		}
	}
}

void sdl_newObject(sdl s ,const void* data) {
	object o =object_create(s ,data);
	list_pushBack(s->object ,o);
}


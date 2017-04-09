#include "sdl.h"
#include <SDL/SDL.h>
#include "list.h"

struct s_sdl {
	SDL_Surface* screen;
	list object;
};

sdl sdl_create() {
	if (SDL_Init(SDL_INIT_VIDEO) ==-1) {
		fprintf(stderr ,"init sdl failed : %s\n" ,SDL_GetError());
		exit(1);
	}

	sdl s =malloc(sizeof(struct s_sdl));

	s->screen =SDL_SetVideoMode(640 ,480 ,32 ,SDL_HWSURFACE);
	SDL_FillRect(s->screen ,NULL ,SDL_MapRGB(s->screen->format ,0x00 ,0xFF ,0xA4));
	SDL_Flip(s->screen);

	return s;
}

void sdl_destroy(sdl* s) {
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

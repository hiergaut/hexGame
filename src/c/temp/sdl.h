#ifndef __SDL__
#define __SDL__

#include <SDL/SDL.h>

#define SDL_BLACK SDL_MapRGB(screen->format, 0x0, 0x0, 0x0)
#define SDL_WHITE SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF)

SDL_Surface* screen;

typedef struct s_sdl* sdl;


sdl sdl_create();
SDL_Surface* sdl_getScreen();
void sdl_destroy(sdl* s);
void sdl_pause();
void sdl_newObject(sdl s, const void* data);
void sdl_link(sdl s, void* data, void* data2);
void sdl_setPos(sdl s, void* data, int dx, int dy, void* data2);
void sdl_setPosByOrigin(sdl s, void* data, int dx, int dy);
void sdl_hexagone(SDL_Surface* area, int x, int y, int l);
void sdl_line(SDL_Surface* area, int x0,int y0, int x1,int y1);
void sdl_floodfill(SDL_Surface* area, int x, int y, Uint32 cr, Uint32 cb);
Uint32 sdl_color(unsigned char r, unsigned char g, unsigned char b);
void sdl_pictureFont(sdl s, const char* file);

#endif

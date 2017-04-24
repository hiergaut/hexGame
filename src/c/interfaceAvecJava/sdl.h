#ifndef __SDL__
#define __SDL__

#include <SDL/SDL.h>

#define SDL_BLACK SDL_MapRGB(screen->format, 0x0, 0x0, 0x0)
#define SDL_WHITE SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF)
#define SDL_RED SDL_MapRGB(screen->format, 0xFF, 0x0, 0x0)

SDL_Surface* screen;

void sdl_create(int width, int height, const char* str);
void sdl_quit();
SDL_Surface* sdl_newSurface(int width, int height, int x, int y, const char* str);
SDL_Surface* sdl_getScreen();
// void sdl_pictureFont(sdl s, const char* file);
void sdl_pause();
void sdl_hexagone(SDL_Surface* area, int x, int y, int l);
void sdl_line(SDL_Surface* area, int x0,int y0, int x1,int y1);
void sdl_floodfill(SDL_Surface* area, int x, int y, Uint32 cr, Uint32 cb);
Uint32 sdl_color(unsigned char r, unsigned char g, unsigned char b);
void sdl_rectangle(SDL_Surface* area, int x1,int y1, int x2, int y2, Uint32 c);
void sdl_square(SDL_Surface* area, int x, int y, int side, Uint32 c);
void sdl_squareFill(SDL_Surface* area, int x, int y, int side, Uint32 c, Uint32 fill);
Uint32 sdl_uniqColorData(void* data);
void sdl_circle(SDL_Surface* area, int xo, int yo, int R, Uint32 c);
void sdl_lineSimple(SDL_Surface* area, int x0,int y0, int x1,int y1, Uint32 c);
void sdl_clean();

#endif

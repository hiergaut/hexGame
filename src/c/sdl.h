#ifndef __SDL__
#define __SDL__

typedef struct s_sdl* sdl;

sdl sdl_create();
void sdl_destroy(sdl* s);
void sdl_pause();
void sdl_newObject(sdl s ,const void* data);

#endif

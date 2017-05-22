#ifndef __INTERFACE__
#define __INTERFACE__

#include <stdbool.h>
#include "graph.h"
#include <SDL/SDL.h>

#define interface_BLACK_PAWN 1
#define interface_WHITE_PAWN 2

// int interface_ENABLE_IA_AUTOPLAY =1;

typedef struct s_interface* interface;

interface interface_create(unsigned side);
void interface_destroy(interface* i);

void interface_placePawn(interface i, int colorPawn, unsigned line, unsigned column);
int interface_getPawn(interface i, unsigned line, unsigned column);
int interface_winner(interface i);

int interface_saveGame(interface i, const char* file);
interface interface_restoreGame(int idGame, const char* file);
// void interface_displayHistory();
int interface_undo(interface i);
int interface_botTakePlace(interface i, int colorPawn);


// sdl
void interface_displayGraph(interface i, graph g, SDL_Surface* area);
void interface_displayPlateau(interface i);
void interface_displayGroup(interface i, int color);

void interface_majScreen(interface i);
void interface_ihm(interface i, int autoPlay);
void interface_displayIhm(interface i);
// end sdl

// getter
int interface_getSide(interface i);
#endif

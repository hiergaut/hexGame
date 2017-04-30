#ifndef __INTERFACE__
#define __INTERFACE__

#include <stdbool.h>
#include "graph.h"
#include <SDL/SDL.h>

#define interface_BLACK_PAWN 1
#define interface_WHITE_PAWN 2

typedef struct s_interface* interface;

interface interface_create(unsigned side);
void interface_destroy(interface* i);

bool interface_legalityPawn(unsigned line, unsigned column);
void interface_placePawn(interface i, int colorPawn, unsigned line, unsigned column);
int interface_getPawn(interface i, unsigned line, unsigned column);
int interface_winner();

int interface_saveGame();
void interface_restoreGame(int idGame);
void interface_displayHistory();
void interface_undo(interface i);

void interface_displayGraph(interface i, graph g, SDL_Surface* area);
void interface_displayPlateau(interface i);
void interface_displayGroup(interface i, int color);

void interface_majScreen(interface i);
void interface_ihm(interface i);
void interface_displayIhm(interface i);

#endif

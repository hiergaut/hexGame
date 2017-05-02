#ifndef __INTERFACE__
#define __INTERFACE__

#include <stdbool.h>
#include "graph.h"
#define interface_BLACK_PAWN 1
#define interface_WHITE_PAWN 2

typedef struct s_interface* interface;

interface interface_create(unsigned side);
void interface_destroy(interface* i);

void interface_placePawn(interface i, int colorPawn, unsigned line, unsigned column);
int interface_getPawn(interface i, unsigned line, unsigned column);
int interface_winner(interface i);

int interface_saveGame();
void interface_restoreGame(int idGame);
void interface_displayHistory();
void interface_undo(interface i);



#endif

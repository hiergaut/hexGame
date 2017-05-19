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

int interface_saveGame(interface i, const char* file);
interface interface_restoreGame(int idGame, const char* file);
// void interface_displayHistory();
int interface_undo(interface i);
void interface_botTakePlace(interface i, int colorPawn);



// getter
int interface_getSide(interface i);
#endif

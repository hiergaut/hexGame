#ifndef __INTERFACE__
#define __INTERFACE__

#include <stdbool.h>

typedef struct s_interface* interface;

interface interface_create(unsigned side);
void interface_destroy(interface* i);

bool interface_legalityPawn(unsigned line, unsigned column);
void interface_placePawn(int colorPawn, unsigned line, unsigned column);
int interface_getPawn(unsigned line, unsigned column);
int interface_winner();

int interface_saveGame();
void interface_restoreGame(int idGame);
void interface_displayHistory();
void interface_undo();

void interface_displayGraphGame(interface i);
void interface_displayPlateau(interface i);
void interface_displayGroup(interface i, int color);


#endif

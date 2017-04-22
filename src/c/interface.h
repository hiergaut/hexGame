#ifndef __INTERFACE__
#define __INTERFACE__

#include <stdbool.h>

typedef struct s_interface* interface;

interface interface_create(unsigned side);
void interface_destroy(interface* i);

bool interface_legalityPawn(unsigned line, unsigned column);
void interface_placePawn(bool black, unsigned line, unsigned column);
int interface_winner();

int interface_saveGame();
void interface_restoreGame(int idGame);
void interface_undo();


#endif

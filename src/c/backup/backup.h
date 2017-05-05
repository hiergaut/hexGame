#ifndef __BACKUP__
#define __BACKUP__

#include "plateau.h"
#include "list.h"
#include "catalog.h"

void backup_printSquare(char* str, plateau p, void* whitePawn, void* blackPawn);
void backup_printData(catalog c, int key, plateau p, list casePlayed, void* whitePawn, void* blackPawn);
int backup_effective(catalog c);
void backup_overWrite(catalog c, int key);
void backup_save(catalog c, int* key, plateau p, list casePlayed, void* whitePawn, void* blackPawn);
int backup_sidePlateau(catalog c, int key);

#endif

#ifndef __INTERFACE__
#define __INTERFACE__

void interface_initPlateau(unsigned side);
int interface_placePawn(bool black, unsigned line, unsigned column);
int interface_winner();
void interface_undo();
void interface_exit();



#endif

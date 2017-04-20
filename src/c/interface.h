#ifndef __INTERFACE__
#define __INTERFACE__

#include <stdbool.h>

typedef struct s_interface* interface;

interface interface_create(unsigned side);
int interface_placePawn(bool black, unsigned line, unsigned column);
int interface_winner();
void interface_undo();
void interface_destroy(interface* i);



#endif

#ifndef __PLATEAU__
#define __PLATEAU__

typedef struct s_plateau* plateau;

plateau plateau_create(unsigned line ,unsigned column);
void plateau_destroy(plateau* p);
void plateau_print(plateau p);
void plateau_insert(plateau p ,unsigned line ,unsigned column ,void* data);


#endif

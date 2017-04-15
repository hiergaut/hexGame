#ifndef __IHM__
#define __IHM__

struct s_pos {
	int x;
	int y;
};
typedef struct s_pos pos;

struct s_ihm {
	int plateauSize;
	pos top;
	int caseHeight;
	int caseSide;
};
typedef struct s_ihm ihm;

ihm ihm_create(int size);
void ihm_printPlateauOnly(ihm m);




#endif

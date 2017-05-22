#ifndef __CATALOG__
#define __CATALOG__

#define CATALOG_BUFFER_MAX 80

typedef struct s_catalog* catalog;

catalog catalog_create(const char* name);
void catalog_destroy(catalog* c);

int catalog_nbOccurrence(catalog c, const char* line);
int catalog_posIthOccurrence(catalog c, const char* line, int ith);
int catalog_nbLine(catalog c);
void catalog_insertAtLine(catalog c, int numLine, const char* sentence);
void catalog_eraseLineBand(catalog c, int firstNumLine, int lastNumLine);
void catalog_getLine(catalog c, int pos, char* str);

#endif

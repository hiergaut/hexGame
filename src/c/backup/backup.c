#include "backup.h"
#include "plateau.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "catalog.h"

#define BACKUP_MAX 80

void backup_printSquare(char* str, plateau p, void* whitePawn, void* blackPawn) {
    int side;
    assert((side =plateau_getNbLine(p)) ==plateau_getNbColumn(p));

    for (int l =0; l <side; l++) {
        for (int c =0; c <side; c++) {
            void* data =plateau_get(p, (unsigned)l, (unsigned)c);
            if (data ==whitePawn)
                strcat(str, "o ");
            else if (data ==blackPawn)
                strcat(str, "* ");
            else
                strcat(str, ". ");
        }
        strcat(str, "\n");
    }
}

void backup_printData(catalog cat, int key, plateau p, list casePlayed, void* whitePawn, void* blackPawn) {
    char str[1024];
    char temp[BACKUP_MAX];

    /* strcat(str, "\\hex\n"); */

    int side;
    assert((side =plateau_getNbLine(p)) ==plateau_getNbColumn(p));
    sprintf(temp, "\\dim %d\n", side);
    strcpy(str, temp);

    strcat(str, "\\board\n");
    backup_printSquare(str, p, whitePawn, blackPawn);
    strcat(str, "\\endboard\n");
    strcat(str, "\\game\n");

    list_it it =list_it_create(casePlayed);
    while (! list_it_end(it)) {
        void* caseCur =list_it_get(it);

        for (int l =0; l <side; l++) {
            for (int c =0; c <side; c++) {
                if (caseCur ==plateau_getPtr(p, (unsigned)l, (unsigned)c)) {
                    char car;
                    void* data =plateau_get(p, (unsigned)l, (unsigned)c);
                    if (data ==whitePawn)
                        car ='o';
                    else if (data ==blackPawn)
                        car ='*';
                    else
                        assert(0);

         
                    sprintf(temp, "\\play %c %d %d\n", car, l, c);
                    strcat(str, temp);
                }
            }
        }
        list_it_next(it);
    }
    list_it_destroy(&it);

    strcat(str, "\\endgame");
    /* strcat(str, "\\endhex\n"); */


    int posHex =catalog_posIthOccurrence(cat, "\\hex", key);
    catalog_insertAtLine(cat, posHex +1, str);
}

int backup_effective(catalog c) {
    return catalog_nbOccurrence(c, "\\endhex");
}

void backup_overWrite(catalog c, int key) {
    int posHex =catalog_posIthOccurrence(c, "\\hex", key);
    int posEndHex =catalog_posIthOccurrence(c, "\\endhex", key);

    catalog_eraseLineBand(c, posHex +1, posEndHex -1);
}

void backup_save(catalog c, int* key, plateau p, list casePlayed, void* whitePawn, void* blackPawn) {
    if (*key ==0) {
        *key =backup_effective(c) +1;

        catalog_insertAtLine(c, catalog_nbLine(c) +1, "\\hex\n\\endhex");
        backup_printData(c, *key, p, casePlayed, whitePawn, blackPawn);

    }
    else {
        assert(*key <=backup_effective(c));

        backup_overWrite(c, *key);
        backup_printData(c, *key, p, casePlayed, whitePawn, blackPawn);
    }
}

int backup_sidePlateau(catalog c, int key) {
    int pos =catalog_posIthOccurrence(c, "\\hex", key);
    char str[BACKUP_MAX];
    catalog_getLine(c, pos +1, str);
    /* printf("str ='%s'\n", str); */
    strcpy(str, &str[5]);
    return atoi(str);
}

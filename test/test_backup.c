#include "backup.h"
#include "plateau.h"
#include <stdio.h>

int main() {

    /* int key =backup_firstMissingKey("saveFile.txt"); */
    /* printf("key =%d\n", key); */

    plateau p =plateau_create(6, 6);
    list casePlayed =list_create();

    int whitePawn;
    int blackPawn;
    int key =1;

    plateau_insert(p, 1, 1, &whitePawn);
    list_pushBack(casePlayed, plateau_getPtr(p, 1, 1));

    plateau_insert(p, 2, 2, &blackPawn);
    list_pushBack(casePlayed, plateau_getPtr(p, 2, 2));

    catalog c =catalog_create("file/saveFile.txt");
    backup_save(c, &key, p, casePlayed, &whitePawn, &blackPawn);

    printf("side plateau =%d\n", backup_sidePlateau(c, 1));


    catalog_destroy(&c);


    plateau_destroy(&p);
    list_destroy(&casePlayed);

    printf("key =%d\n" ,key);


    return 0;
}

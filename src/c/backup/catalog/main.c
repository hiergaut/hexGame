#include "catalog.h"
#include <stdio.h>

int main() {

    catalog c =catalog_create("file.txt");

    printf("nb occ a =%d\n", catalog_nbOccurrence(c, "a"));
    printf("nb occ b =%d\n", catalog_nbOccurrence(c, "b"));
    printf("nb occ z =%d\n", catalog_nbOccurrence(c, "z"));
    printf("nb occ ab =%d\n", catalog_nbOccurrence(c, "ab"));

    printf("pos 1er a =%d\n", catalog_posIthOccurrence(c, "a", 1));
    printf("pos 2eme a =%d\n", catalog_posIthOccurrence(c, "a", 2));
    printf("pos 1er ab =%d\n", catalog_posIthOccurrence(c, "ab", 1));
    /* printf("pos 1er z =%d\n", catalog_posIthOccurrence(c, "z", 1)); */
    /* printf("pos 2eme g =%d\n", catalog_posIthOccurrence(c, "g", 2)); */
    printf("nb line =%d\n", catalog_nbLine(c));
    catalog_insertAtLine(c, catalog_nbLine(c) +1, "test 1\ntest 2");
    catalog_eraseLineBand(c, 2, 2);

    char str[80];
    catalog_getLine(c, 1, str);
    printf("getLine ='%s'\n", str);

    catalog_destroy(&c);

    return 0;
}

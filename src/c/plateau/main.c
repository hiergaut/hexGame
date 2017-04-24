#include "plateau.h"
#include <stdio.h>

int main() {

    plateau p =plateau_create(5, 9);

    int a =5;
    plateau_insert(p, 4, 3, &a);
    plateau_print(p);

    printf("%d" ,*(int*)plateau_get(p, 4, 3));

    plateau_destroy(&p);

    return 0;
}

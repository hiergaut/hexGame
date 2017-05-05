#include "interface.h"
#include <stdio.h>

int main() {

    interface i =interface_create(5);
    printf("test");
    interface_saveGame(i, "file.txt");

    interface_destroy(&i);


    return 0;
}

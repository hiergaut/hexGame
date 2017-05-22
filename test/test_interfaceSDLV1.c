/* #include "plateau.h" */
/* #include <stdio.h> */
/* #include "graph.h" */
/* #include "sdl.h" */
/* #include <math.h> */
/* #include "ihm.h" */
/* #include <SDL/SDL.h> */
/* #include <unistd.h> */
/* #include <wait.h> */
/* #include <stdlib.h> */
#include "interface.h"
#include <stdio.h>
#include "sdl.h"

int main() {
    /* char file[] ="file/interfaceSDLV1.txt"; */

    interface i =interface_create(9);

    /* interface i =interface_restoreGame(1, file); */

    int autoPlay =0;
    interface_ihm(i, autoPlay);
    /* interface_botTakePlace(i, interface_BLACK_PAWN); */
    /* interface_saveGame(i, file); */


    interface_destroy(&i);


    return 0;
}

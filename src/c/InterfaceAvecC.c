#include <stdlib.h>
#include "InterfaceAvecC.h"
#include "interface.h"

interface global_interface =NULL;

JNIEXPORT void JNICALL 
Java_InterfaceAvecC_newGame(JNIEnv *env, jclass c1, jint ji) {
    global_interface =interface_create(ji);
}

JNIEXPORT void JNICALL 
Java_InterfaceAvecC_endGame(JNIEnv *env, jclass c1) {
    interface_destroy(&global_interface);
}

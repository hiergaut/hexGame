#include <stdlib.h>
#include "InterfaceAvecC.h"
#include "interface.h"

interface i;

JNIEXPORT void JNICALL 
Java_InterfaceAvecC_createPlateau(JNIEnv *env, jclass c1, jint ji) {
    i =interface_create(ji);

}

JNIEXPORT void JNICALL 
Java_InterfaceAvecC_destroyPlateau(JNIEnv *env, jclass c1) {
    interface_destroy(&i);

}

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

JNIEXPORT jboolean JNICALL 
Java_InterfaceAvecC_permission(JNIEnv *env, jclass c1, jint line, jint column) {
    return interface_legalityPawn(line, column);
}

JNIEXPORT void JNICALL 
Java_InterfaceAvecC_setPawn(JNIEnv *env, jclass c1, jboolean blackPawn, jint line, jint column) {
    interface_placePawn(blackPawn, line, column);
}

JNIEXPORT jint JNICALL 
Java_InterfaceAvecC_hasAWinner(JNIEnv *env, jclass c1) {
    return interface_winner();
}

JNIEXPORT int JNICALL 
Java_InterfaceAvecC_saveGame(JNIEnv *env, jclass c1) {
    interface_saveGame();
}

JNIEXPORT void JNICALL 
Java_InterfaceAvecC_restoreGame(JNIEnv *env, jclass c1, jint idGame) {
    interface_restoreGame(idGame);
}

JNIEXPORT void JNICALL 
Java_InterfaceAvecC_undo(JNIEnv *env, jclass c1) {
    interface_undo();
}

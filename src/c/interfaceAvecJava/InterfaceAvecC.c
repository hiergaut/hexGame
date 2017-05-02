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


JNIEXPORT void JNICALL 
Java_InterfaceAvecC_insertPawn(JNIEnv *env, jclass c1, jint colorPawn, jint line, jint column) {
    interface_placePawn(global_interface, colorPawn, line, column);
}

JNIEXPORT jint JNICALL 
Java_InterfaceAvecC_getPawn(JNIEnv *env, jclass c1, jint line, jint column) {
    return interface_getPawn(global_interface, line, column);
}

JNIEXPORT jint JNICALL 
Java_InterfaceAvecC_hasAWinner(JNIEnv *env, jclass c1) {
    return interface_winner(global_interface);
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
Java_InterfaceAvecC_displayHistoryGame(JNIEnv *env, jclass c1) {
    interface_displayHistory();
}

JNIEXPORT jint JNICALL 
Java_InterfaceAvecC_undo(JNIEnv *env, jclass c1) {
    interface_undo(global_interface);
}

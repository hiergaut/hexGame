
class InterfaceAvecC {
    static {
	System.loadLibrary("InterfaceAvecC");
    }
    public static native void newGame(int sizeOfPlateau);
    public static native void endGame();


}

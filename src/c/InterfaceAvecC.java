
class InterfaceAvecC {
    static {
	System.loadLibrary("InterfaceAvecC");
    }
    public static native void createPlateau(int side);
    public static native void destroyPlateau();


}

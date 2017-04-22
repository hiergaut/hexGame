
public class InterfaceAvecC {
    static {
	System.loadLibrary("InterfaceAvecC");
    }
    /**
     * create a graph of plateau, and group of player's pawn
     * @param sizeOfPlateau describe the side of plateau, including width and height
     */
    public static native void newGame(int sizeOfPlateau);

    /**
     * to free all data structure representing the game in c
     */
    public static native void endGame();

    /**
     * permit to place a pawn
     * @param line of plateau to insert pawn
     * @param column of plateau to insert pawn
     */
    public static native boolean permission(int line, int column);

    /**
     * place a pawn black or white in plateau's square
     * @param blackPawn black piece if true obviously
     * @param line plateau's line
     * @param column plateau's column
     */
    public static native void setPawn(boolean blackPawn, int line, int column);

    /**
     * looks for the winner
     * @return 0 if no winner, 1 if Black winner, 2 if White winner
     * no egality on Hex game
     */
    public static native int hasAWinner();

    /**
     * save status game on database implement in c, maybe in SQL
     * if you save an already saved party then it erase the previous save for the new
     * @return integer representative an uniq key of curent game
     */
    public static native int saveGame();

    /**
     * restore previous game, before that you must quit the current game
     * @param idGame uniq key code of previous game
     */
    public static native void restoreGame(int idGame);

    /**
     * if a player make a wrong shot, he can resume game, one pawn a time
     * undo if an empty plateau, assume your consequence, 
     * program will be interrupted
     */
    public static native void undo();

}

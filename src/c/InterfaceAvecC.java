
public class InterfaceAvecC {
    static {
	System.loadLibrary("InterfaceAvecC");
    }

    public final static int BLACK_PAWN =1;
    public final static int WHITE_PAWN =2;
    public final static int EMPTY_PAWN =0;

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
     * @return true if permit to take a place (empty case)
     */
    public static native boolean permission(int line, int column);

    /**
     * place a pawn black or white in plateau's square
     * @param colorPawn use final variable BLACK_PAWN, WHITE_PAWN, EMPTY_PAWN
     * @param line plateau's line
     * @param column plateau's column
     */
    public static native void setPawn(int colorPawn, int line, int column);

    /**
     * return color of a specific case, 0 if empty, 1 if Black, 2 if White
     * @param line plateau's line
     * @param column plateau's column
     */
    public static native int getPawn(int line, int column);

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
     * display history database, help for restoration
     */
    public static native void displayHistoryGame();

    /**
     * if a player make a wrong shot, he can resume game, one pawn a time
     * undo if an empty plateau, assume your consequence, 
     * program will be interrupted
     */
    public static native void undo();

    /**
     * display graph implement in C
     */
    public static native void displayGraphGame();

    /**
     * display plateau implement in C, just for debuging and this plateau is
     * a duty to create plateau's graph, and for write plateau in a text file
     * for database save
     */
    public static native void displayPlateau();

    /**
     * display group of each player specify
     * @param colorPlayer you can use WHITE_PAWN, BLACK_PAWN
     * but not EMPTY_PAWN because no group for empty color (empty case)
     */
    public static native void displayGroup(int colorPlayer);
}

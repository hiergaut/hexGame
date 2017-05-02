
public class InterfaceAvecC {
    static {
        System.loadLibrary("InterfaceAvecC");
    }

    public final static int NO_PAWN =0;

    public final static int BLACK_PAWN =1;
    public final static int WHITE_PAWN =2;

    /**
     * create data structure in C which are :
     *      - plateau (allow creation of graph and fast save on text file)
     *      - graph (permit group and reduceGraph)
     *      - group of black/white player
     *      - reduceGraph (for calculation of game)
     * @param sizeOfPlateau describe the side of plateau, including width and height
     */
    public static native void newGame(int sizeOfPlateau);

    /**
     * to free all data structure of current interface, representing the game in C
     */
    public static native void endGame();

    /**
     * place a black/white pawn on plateau's square
     * @param colorPawn use constant variable (BLACK_PAWN, WHITE_PAWN)
     * you can't use EMPTY_PAWN, you must use undo to go backward in a game
     * undo manage the history of play for each player of the current party
     * @param line plateau's line
     * @param column plateau's column
     * assert if out of range line or column 
     * and if you insert pawn on a already full case
     */
    public static native void insertPawn(int colorPawn, int line, int column);

    /**
     * return color int constant of a specific case (NO_PAWN, BLACK_PAWN, WHITE_PAWN)
     * @param line plateau's line
     * @param column plateau's column
     * assert if out of range line/column
     */
    public static native int getPawn(int line, int column);

    /**
     * looks for the winner
     * @return 0 if no winner, otherwise winner's color (BLACK_PAWN, WHITE_PAWN)
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
     * @return the color of pawn (BLACK_PAWN, WHITE_PAWN) who was delete on plateau
     * 0 if no pawn in the game so no undo to do
     */
    public static native int undo();

}

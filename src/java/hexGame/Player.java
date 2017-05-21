import java.util.Scanner;

class Player {
    protected String name;
    protected int pawn;
    protected String edge;
    protected int round = 0;
    protected int move_number = 0;
    protected String lastMove = " - - - ";
    protected boolean isStarting = true;

    /**
     * Constructor of Player Class
     * @param pawn, the pawn the player will use
     * @param edge, the edges the player need to link to win
     */
    public Player(int pawn, String edge) {
	this.pawn = pawn;
	this.edge = edge;
    }

    /**
     * Getter for the name of the player
     * @return the name of the player
     */
    public String getName() {
	return this.name;
    }

    /**
     * Sets the name of the player
     * @param n, the new name of the player */
    public void setName(String name) {
	this.name = name;
    }

    /**
     * Getter for the pawn of the player
     * @return the pawn of the player
     */
    public int getPawn() {
	return this.pawn;
    }

    /**
     * Getter for the edge of the player
     * @return the edge of the player
     */
    public String getEdge() {
	return this.edge;
    }

    /**
     * Getter for the current round of the player
     * @return the current round
     */
    public int getRound() {
	return round;
    } 

    /**
     * Increment the round number
     */
    public void incRound() {
	++round;
    }

    /**
     * Decrement the round number
     */
    private void decRound(){
	--round;
    }

    /**
     * Getter for the number of moves the player has made
     * @return the number of moves
     */
    public int getMoveNumber() {
	return this.move_number;
    }

    /**
     * Getter for the last move of the player
     * @return the last move made by the player
     */
    public String getLastMove() {
	return this.lastMove;
    }

    /**
     * Getter the starting status
     * @return if the player is starting
     */
    public boolean getStartingStatus() {
	return this.isStarting;
    }

    /**
     * Switch the starting status
     */
    public void switchStarting() {
	isStarting = isStarting ? false : true;
    }

    /**
     * The player play his turn
     * @param s, the scanner for I/O
     */
    public boolean play(Player p1, Player p2, int size, Scanner s) {
	boolean notOver = false;
	while (!notOver) {
	    Functions.printInfos(this);
	    Functions.displayBoard(p1,p2,size);
	    Functions.printActionMenu();
	    switch (s.nextInt()) {
		case 1:
		    placeAPawn(s);
		    break;
		case 2:
		    s.nextLine();
		    Game.savedGame = saveGame(s);
		    break;
		case 3:
		    cancelMove();
		    break;
		case 4:
		    return true;
		case 5:
		    notOver = endTurn();
		    break;
		default:
		    System.out.println("Choix invalide");
		    break;
	    }
	}
	return false;

    }

    /**
     * The player place a pawn on the board
     * @param s, the scanner for I/O
     */
    private void placeAPawn(Scanner s) {
	boolean isPossible = false;
	while (!isPossible) {
	    System.out.println("Ou posez le pion ?");
	    int i,j;
	    i = (s.nextInt() - 1) % Game.boardSize ;
	    j = (s.nextInt() - 1) % Game.boardSize;
	    s.nextLine();

	    if (InterfaceAvecC.getPawn(i,j) == InterfaceAvecC.NO_PAWN) {
		InterfaceAvecC.insertPawn(getPawn(),i,j);
		lastMove = "row " + (i + 1) + " col " + (j + 1);
		incRound();
		isPossible = true;

	    }
	    else {
		System.out.println("Action impossible ! \n");
	    }
	}
    }

    /**
     * The player saves the current state of the game
     */
    private int saveGame(Scanner s) {
	System.out.println("Entrez le nom de la sauvegarde:");
	String saveName = s.nextLine();
	return InterfaceAvecC.saveGame(saveName);
    }

    /**
     * The player cancel his last move
     */
    private void cancelMove() {
	InterfaceAvecC.undo();
	decRound();
    }

    private boolean endTurn() {
	System.out.println("Fin du tour!");
	return true;
    }



}

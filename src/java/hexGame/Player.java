//package hexGame;

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
     * @param n, the new name of the player
     */
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
     * @return the new round
     */
    public void incRound() {
	++round;
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
     * @param b, the board of which the player plays
     * @param s, the scanner for I/O
     */
    public void play(Scanner s) {

	boolean isPossible = false;
	while (!isPossible) {
	    System.out.println();
	    System.out.println("Ou posez le pion ?");
	    int i,j;
	    i = (s.nextInt() - 1) % Game.boardSize ;
	    j = (s.nextInt() - 1) % Game.boardSize;

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
    

}

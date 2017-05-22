
/*****************************************************************/
/*								 */
/*			HexGame - Projet			 */
/*			  Player Class 	  			 */
/*			Jonathan Lao-Kan			 */
/*			   22 mai 2017				 */
/*								 */
/*****************************************************************/

import java.util.*;
import java.io.*;

class Player {
    protected String name;
    protected int pawn;
    protected String edge;
    protected int round = 0;
    protected boolean hasPlayed = false;
    protected String lastMove = " - - - ";
    protected boolean isStarting = true;
    protected boolean isPlaying;

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
     * Setter for the pawn of the player
     * @param p, the new pawn of the player
     */
    public void setPawn(int p) {
	this.pawn = p;
    }

    /**
     * Getter for the edge of the player
     * @return the edge of the player
     */
    public String getEdge() {
	return this.edge;
    }

    /**
     * Setter for the edge of the player
     * @param e, the new edge of the player
     */
    public void setEdge(String e) {
	this.edge = e;
    }

    /**
     * Getter for the current round of the player
     * @return the current round
     */
    public int getRound() {
	return round;
    } 

    /**
     * Setter for the current round of the player
     * @param r, the current round
     */
    public void setRound(int r) {
	this.round = r;
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
     * Get if this player already made a move 
     * @return true or false
     */
    public boolean getHasPlayed() {
	return this.hasPlayed;
    }

    /**
     * Setter for the hasPlayed boolean
     * @param b, the new value
     */
    public void setHasPlayed(boolean b) {
	this.hasPlayed = b;
    }

    /**
     * Getter for the last move of the player
     * @return the last move made by the player
     */
    public String getLastMove() {
	return this.lastMove;
    }

    /**
     * Setter for the last move of the player
     * @param lm, the last move made
     */
    public void setLastMove(String lm) {
	this.lastMove = lm;
    }

    /**
     * Getter the starting status
     * @return if the player is starting
     */
    public boolean getStartingStatus() {
	return this.isStarting;
    }

    /**
     * Set the current starting status
     * @param s, the new status
     */
    public void setStartingStatus(boolean s) {
	isStarting = s;
    }

    /**
     * Switch the starting status
     */
    public void switchStarting() {
	isStarting = isStarting ? false : true;
    }

    /**
     * Getter for the playing status
     * @return the playing status
     */
    public boolean getPlaying() {
	return this.isPlaying;
    }

    /**
     * Setter for the playing status
     * @return the starting status
     */
    public void setPlaying(boolean s) {
	this.isPlaying = s;
    }

    /**
     * The player play his turn
     * @param s, the scanner for I/O
     */
    public boolean play(Player p1, Player p2, int size, Scanner s) {
	setPlaying(true);
	while (getPlaying()) {
	    Functions.clearScreen();
	    Functions.printInfos(this);
	    Functions.displayBoard(p1,p2,size);
	    Functions.printActionMenu();
	    switch (s.nextInt()) {
		case 1:
		    if (!this.getHasPlayed()) {
			placeAPawn(s);
		    }
		    else {
			System.out.println("You already played this turn");
		    }
		    break;
		case 2:
		    s.nextLine();
		    saveGame(p1,p2,s);
		    break;
		case 3:
		    cancelMove();
		    break;
		case 4:
		    return true;
		case 5:
		    setPlaying(endTurn());
		    break;
		default:
		    System.out.println("Invalid choice");
		    break;
	    }
	}
	setPlaying(false);
	return getPlaying();

    }

    /**
     * The player place a pawn on the board
     * @param s, the scanner for I/O
     */
    private void placeAPawn(Scanner s) {
	boolean isPossible = false;
	while (!isPossible) {
	    System.out.print("Where do you want to play : ");
	    int i,j;
	    i = (s.nextInt() - 1) % Game.boardSize ;
	    j = (s.nextInt() - 1) % Game.boardSize;
	    s.nextLine();

	    if (InterfaceAvecC.getPawn(i,j) == InterfaceAvecC.NO_PAWN) {
		InterfaceAvecC.insertPawn(getPawn(),i,j);
		lastMove = "row " + (i + 1) + " col " + (j + 1);
		incRound();
		isPossible = true;
		setHasPlayed(true);

	    }
	    else {
		System.out.println("Impossible choice\n");
	    }
	}
    }

    /**
     * The player saves the current state of the game
     */
    private void saveGame(Player p1, Player p2, Scanner s) {
	System.out.print("Name of savefile : ");
	String saveName = s.nextLine();
	try {
	    FileWriter w = new FileWriter(saveName + Game.SAVEJ);
	    w.write(Integer.toString(Game.boardSize) + '\n');
	    int gameId = InterfaceAvecC.saveGame(saveName + Game.SAVEG); 
	    w.write(Integer.toString(gameId) + '\n');
	    w.close();
	}
	catch (Exception e) {
	    e.printStackTrace();
	}
	p1.saveInfos(saveName + Game.SAVEJ);
	p2.saveInfos(saveName + Game.SAVEJ);
    }

    /**
     * The player cancel his last move
     */
    private void cancelMove() {
	InterfaceAvecC.undo();
	decRound();
	setHasPlayed(false);
    }

    /**
     * End the turn of the player
     */
    private boolean endTurn() {
	System.out.println("Fin du tour!");
	this.setHasPlayed(false);
	return false;
    }

    /**
     * Saves player's info to a textfile
     * @param filename, the name of the file
     */
    private void saveInfos(String filename) {
	try {
	    FileWriter w = new FileWriter(filename,true);
	    w.write(getName() + '\n');
	    w.write(Integer.toString(getPawn()) + '\n');
	    w.write(getEdge() + '\n');
	    w.write(Integer.toString(getRound()) + '\n');
	    w.write(Boolean.toString(getHasPlayed()) + '\n');
	    w.write(getLastMove() + '\n');
	    w.write(Boolean.toString(getStartingStatus()) + '\n');
	    w.write(Boolean.toString(getPlaying()) + '\n');
	    w.close();
	}
	catch (Exception e) {
	    e.printStackTrace();
	}
    }
}

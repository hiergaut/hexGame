package hexGame;

class Player {
    protected String name;
    protected char pawn;
    protected char edge;
    protected int round = 0;
    protected int move_number = 0;
    protected String lastMove;

    /**
     * Constructor of Player Class
     * @param name, the name of the player
     * @param pawn, the pawn the player will use
     * @param edge, the edges the player need to link to win
     */
    public Player(String name, char pawn, char edge) {
	this.name = name;
	this.pawn = pawn;
	this.edge = edge;
	this.lastMove = getName() + " started the game";
    }

    /**
     * Getter for the name of the player
     * @return the name of the player
     */
    public String getName() {
	return this.name;
    }

    /**
     * Getter for the pawn of the player
     * @return the pawn of the player
     */
    public char getPawn() {
	return this.pawn;
    }

    /**
     * Getter for the edge of the player
     * @return the edge of the player
     */
    public char getEdge() {
	return this.edge;
    }

    /**
     * Getter for the current round of the player
     * @return the current round
     */
    public int getRound() {
	return this.round;
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
    

}

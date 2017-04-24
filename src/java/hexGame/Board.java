package hexGame;

public class Board {
    protected int size = 11;
    protected Square[][] squares;
    protected Player p1;
    protected Player p2;

    /**
     * Constructor of Board Class
     */
    public Board() {
	this.squares = new Square[size][size];
	this.init();
    }

    private void init() {
	for (int i = 0; i <this.size; i++) {
	    for (int j = 0; j < this.size; j++) {
		squares[i][j] = new Square();
	    }
	}
    }

    /**
     * Setter of size
     * @param n, sets the board to n*n
     */
    public void setSize(int n) {
	size = n;
    }

    /**
     * Get the size of the board
     * 
     */
    public int getSize() {
	return this.size;
    }

    /**
     * Get the first player
     */
    public Player getPlayer1(){
	return this.p1;
    }

    /**
     * Get the second player
     */
    public Player getPlayer2(){
	return this.p2;
    }

    /**
     * Set the player 1
     */
    public void setPlayer1(Player p) {
	p1 = p;
    }

    /**
     * Set the player 2
     */
    public void setPlayer2(Player p) {
	p2 = p;
    }

    public void display() {
	display_edges();
	for (int i = 0; i < this.size; i++) {
	    for (int j =0; j <= i; j++)
		System.out.print(" ");

	    System.out.print(p1.getEdge());
	    for (int j =0 ;j < this.size; j++) {
		System.out.print(" " + squares[i][j].getPawn());
	    }
	    System.out.print(" ");
	    System.out.print(p1.getEdge());
	    System.out.println();
	}

	for (int i = 0; i <= this.size; i++) {
	    System.out.print(" ");
	}
	display_edges();
    }

    private void display_edges() {
	System.out.print(p1.getEdge() + "\\" + p2.getEdge());
	for (int i = 1; i <= this.size - 2 ; i++) {
	    System.out.print(" " + p2.getEdge());
	}
	System.out.print(" " + p2.getEdge() + "\\" + p1.getEdge() + "\n");
    }
}

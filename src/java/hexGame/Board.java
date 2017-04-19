package hexGame;

public class Board {
    protected int size;
    protected Space[][] s;
    protected Player p1;
    protected Player p2;

    /**
     * Constructor of Board Class
     * @param size, the size of the side of the board
     * @param p1, the first player
     * @param p2, the second player
     */
    public Board(int size, Player p1, Player p2) {
	this.size  = size;
	this.s = new Space[size][size];
	this.p1 = p1;
	this.p2 = p2;
	this.init();
    }

    private void init() {
	for (int i = 0; i <this.size; i++) {
	    for (int j = 0; j < this.size; j++) {
		s[i][j] = new Space();
	    }
	}
    }

    void display() {
	System.out.print(p1.getEdge() + "\\" + p2.getEdge());

	for (int i = 1; i <= this.size - 2 ; i++) {
	    System.out.print(" " + p2.getEdge());
	}

	System.out.print(" " + p2.getEdge() + "\\" + p1.getEdge() + "\n");


	for (int i = 0; i < this.size; i++) {
	    for (int j =0; j <= i; j++)
		System.out.print(" ");

	    System.out.print(p1.getEdge());
	    for (int j =0 ;j < this.size; j++) {
		System.out.print(" " + s[i][j].toString());
	    }
	    System.out.print(" ");
	    System.out.print(p1.getEdge());
	    System.out.println();
	}

	for (int i = 0; i <= this.size; i++) {
	    System.out.print(" ");
	}
	System.out.print(p1.getEdge() + "\\" + p2.getEdge());

	for (int i = 1; i <= this.size - 2 ; i++) {
	    System.out.print(" " + p2.getEdge());
	}

	System.out.print(" " + p2.getEdge() + "\\" + p1.getEdge() + "\n");
    }
}

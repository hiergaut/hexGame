package hexGame;

public class Board {
    protected int width;
    protected int length;
    protected Space[][] s;
    protected Player p1;
    protected Player p2;

    public Board(int width, int length, Player p1, Player p2) {
	this.width = width;
	this.length = length;
	this.s = new Space[width][length];
	this.p1 = p1;
	this.p2 = p2;
	this.init();
    }

    private void init() {
	for (int i =0; i <this.width; i++) {
	    for (int j =0; j <this.length; j++) {
		s[i][j] =new Space();
	    }
	}
    }

    void display() {
	System.out.print(p2.getEdge());
	for (int i =1; i <= this.length; i++) {
	    System.out.print(" " + p2.getEdge());
	}
	System.out.print("\\" + p1.getEdge() +"\n");

	for (int i =0; i < this.width; i++) {
	    for (int j =0; j <= i; j++)
		System.out.print(" ");

	    System.out.print(p1.getEdge());
	    for (int j =0 ;j <this.length ;j++) {
		System.out.print(" " + s[i][j].toString());
	    }
	    System.out.print(" ");
	    System.out.print(p1.getEdge());
	    System.out.println();
	}

	for (int i =0; i <this.width; i++) {
	    System.out.print(" ");
	}

    }
}

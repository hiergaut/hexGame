package hexGame;

class Player {
    protected String name;
    protected char pawn;
    protected char edge;

    public Player(String name, char pawn, char edge) {
	this.name = name;
	this.pawn = pawn;
	this.edge = edge;
    }

    char getEdge() {
	return this.edge;
    }
}

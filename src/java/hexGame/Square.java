//package hexGame;

public class Square {
    protected boolean isEmpty;
    protected char currPawn;

    public Square() {
	this.isEmpty = true;
	this.currPawn = '.';
    }

    public void setIsEmpty(boolean b) {
	isEmpty = b;
    }

    public char getPawn() {
	return currPawn;
    }

    public void setPawn(char pawn) {
	currPawn = pawn;
	isEmpty = false;
    }



}

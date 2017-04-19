package hexGame;

public class Square {
    protected boolean empty;
    protected boolean leftPlayer;

    Square() {
	this.empty = true;
    }

    public String toString() {
	if (this.empty) {
	    return ".";
	}
	return "a";
    }
}

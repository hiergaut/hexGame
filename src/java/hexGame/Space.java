package hexGame;

public class Space {
    protected boolean empty;
    protected boolean leftPlayer;

    Space() {
	this.empty = true;
    }

    public String toString() {
	if (this.empty) {
	    return ".";
	}
	return "a";
    }
}

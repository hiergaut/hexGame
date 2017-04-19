package hexGame; 

public class Game {
    public static void main(String[] args) {
	int n = 11;
	Player p1 = new Player("gauthier" ,'B' ,'B');
	Player p2 = new Player("florent" ,'W' ,'W');
	Board b = new Board(n, p1, p2);
	b.display();

    }
}

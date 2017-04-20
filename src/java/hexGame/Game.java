package hexGame; 

public class Game {
    public static void main(String[] args) {
	//int n = 11;
	Player p1 = new Player("gauthier" ,'B' ,'B');
	Player p2 = new Player("florent" ,'W' ,'W');
	//Board b = new Board(n, p1, p2);
	//b.display();
	Functions.print_menu();

	System.out.println();

	Functions.print_infos(p1);
	Functions.print_infos(p2);
    }
}

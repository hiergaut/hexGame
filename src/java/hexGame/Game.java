import java.util.Scanner;

public class Game {

    protected static int boardSize = 4;
    protected static final String RED = "\u001b[41m \u001b[0m";
    protected static final String BLUE = "\u001b[44m \u001b[0m";
    protected static final String WHITE = "\u001b[47m \u001b[0m";

    private static void startGameC(Player p1, Player p2, Scanner s) {
	boolean gameover = false;
	int gameStatus;
	Player starting;
	Player challenger;

	starting = p1.getStartingStatus() ? p1 : p2;
	challenger = p1.getStartingStatus() ? p2 : p1;

	System.out.println(starting.getName() + " starts the game !");
	while (!gameover) {
	    Functions.printInfos(starting);
	    Functions.displayBoard(p1,p2,boardSize);
	    starting.play(s);
	    if (Functions.undo(s)) {
		starting.play(s);
	    }
	    
	    if ( (gameStatus = InterfaceAvecC.hasAWinner()) != 0 ) {
		System.out.println( starting.getName() + " remporte la partie !" );
		Functions.displayBoard(p1,p2,boardSize);
		break;
	    }

	    Functions.printInfos(challenger);
	    Functions.displayBoard(p1,p2,boardSize);

	    challenger.play(s);

	    if (Functions.undo(s)) {
		challenger.play(s);
	    }

	    if ( (gameStatus = InterfaceAvecC.hasAWinner()) != 0 ) {
		System.out.println( challenger.getName() + " remporte la partie !" );
		Functions.displayBoard(p1,p2,boardSize);
		break;
	    }
	}
    }

    public static void main(String[] args) {
	Scanner scan = new Scanner(System.in);
	Player p1 = new Player(2,BLUE);
	Player p2 = new Player(1,RED);
	boolean wantsToQuit = false;



	while (!wantsToQuit) {
	    Functions.printMenu();
	    InterfaceAvecC.newGame(boardSize);
	    switch ( scan.nextInt() ) {
		case 1:
		    Functions.printSubMenu();
		    switch ( scan.nextInt() ) {
			case 1:
			    System.out.println("Partie contre IA ! ");
			    break;
			case 2:
			    System.out.println("Humain contre Humain ! ");
			    p1.setName(Functions.askPlayerName(1,scan));
			    p2.setName(Functions.askPlayerName(2,scan));
			    startGameC(p1,p2,scan);
			    break;
			case 3:
			    break; 
			default:
			    System.out.println("Choix invalide");
			    break;
		    }
		    break;
		case 2:
		    System.out.println("Menu options");
		    Functions.printOptions(p1,p2);
		    switch ( scan.nextInt() ) {
			case 1:
			    boardSize = Functions.askBoardSize(scan);
			    InterfaceAvecC.endGame();
			    InterfaceAvecC.newGame(boardSize);
			    break;
			case 2:
			    p1.switchStarting();
			    break;
			case 3:
			    break; 
			default:
			    System.out.println("Choix invalide");
			    break;
		    }
		    break;
		case 3:
		    System.out.println("Goodbye !");
		    wantsToQuit = true;
		    break;
		default:
		    System.out.println("Choix invalide");
		    break;
	    }

	}

	scan.close();




	
	
	

    }
}

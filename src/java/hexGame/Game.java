//package hexGame; 

import java.util.Scanner;

public class Game {

    //private static void startGame(Board b, Scanner s) {
    //    boolean gameover = false;
    //    Player starting;
    //    Player challenger;

    //    starting = b.getPlayer1().getStartingStatus() ? b.getPlayer1() : b.getPlayer2();
    //    challenger = b.getPlayer1().getStartingStatus() ? b.getPlayer2() : b.getPlayer1();

    //    System.out.println(starting.getName() + " starts the game !");
    //    while (!gameover) {
    //        Functions.printInfos(starting);
    //        b.display();
    //        starting.play(b,s);
    //        Functions.printInfos(challenger);
    //        b.display();
    //        challenger.play(b,s);
    //    }
    //}

    private static void startGameC(Player p1, Player p2, Scanner s) {
	boolean gameover = false;
	Player starting;
	Player challenger;

	starting = p1.getStartingStatus() ? p1 : p2;
	challenger = p1.getStartingStatus() ? p2 : p1;

	System.out.println(starting.getName() + " starts the game !");
	while (!gameover) {
	    Functions.printInfos(starting);
	    Functions.displayBoard(p1,p2,11);
	    starting.play(s);
	    Functions.printInfos(challenger);
	    Functions.displayBoard(p1,p2,11);
	    challenger.play(s);
	}
    }

    public static void main(String[] args) {
	Scanner scan = new Scanner(System.in);
	Player p1 = new Player(2,'W');
	Player p2 = new Player(1,'B');
	boolean wantsToQuit = false;
	InterfaceAvecC.newGame(11);



	while (!wantsToQuit) {
	    Functions.printMenu();
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
			    //b.setSize(Functions.askBoardSize(scan));
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

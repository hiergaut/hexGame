import java.util.Scanner;

public class Functions {

    /**
     * Display the starting menu
     */
    public static void printMenu() {
	System.out.println();
	System.out.println("1. Start");
	System.out.println("2. Load");
	System.out.println("3. Options");
	System.out.println("4. Exit");
	System.out.println();
    }

    /**
     * Display the second menu
     */
    public static void printSubMenu() {
	System.out.println();
	System.out.println("1. 1 Player");
	System.out.println("2. 2 Player");
	System.out.println("3. Return");
	System.out.println();
    }

    /**
     * Display the player's action menu
     */
    public static void printActionMenu() {
	System.out.println();
	System.out.println("1. Place a pawn \t\t 2. Save the game \t\t 5.End Turn");
	System.out.println("3. Cancel last move \t\t 4. Give up.");
	System.out.println();

    }
     
    /**
     * Display overhead infos of current game
     */
    public static void printInfos(Player player) {
	System.out.println();
	System.out.printf("Nom: %-10s",player.getName());
	System.out.printf("Tour: %-10s",player.getRound());
	System.out.printf("Derniere action de %s : %-10s", player.getName(), player.getLastMove());
	System.out.println();
	System.out.println();
    }

    /**
     * Display the options menu
     */
    public static void printOptions(Player p1, Player p2) {
	System.out.println();
	System.out.printf("1. Change the size of the Board (Curr : %d)", Game.boardSize);
	System.out.println();
	System.out.printf("2. Change the starting player (Curr : %s)",p1.isStarting ? 
	Game.RED : Game.BLUE );
	System.out.println();
	System.out.println("3. Back");
	System.out.println();
	System.out.println();
    }

    /**
     * Ask the size of the board
     * @param s, the scanner to read I/O
     * @return the size of the board
     */
    public static int askBoardSize(Scanner s) {
	int boardSize;

	System.out.println("Taille du plateau : ");
	boardSize = s.nextInt();
	
	return boardSize;
    }

    /**
     * Ask the name of a player
     * @param num, the player's number ( 1 or 2 )
     * @param s, the scanner to read I/O
     * @return the player's name
     */
    public static String askPlayerName(int num, Scanner s) {
	String playerName;

	System.out.println("Nom du joueur " + num + " ?");
	playerName = s.next();

	return playerName;
    }

    /**
     * Display the current board
     * @param size, the size of the board
     */
    public static void displayBoard(Player p1, Player p2, int size) {
	display_edges(p1,p2,size);
	for (int i = 0; i < size; i++) {
	    for (int j =0; j <= i; j++)
		System.out.print(" ");

	    System.out.print(p1.getEdge());
	    for (int j =0 ;j < size; j++) {
		System.out.print(" " + displayPawn(InterfaceAvecC.getPawn(i,j)));
	    }
	    System.out.print(" ");
	    System.out.print(p1.getEdge());
	    System.out.println();
	}

	for (int i = 0; i <= size; i++) {
	    System.out.print(" ");
	}
	display_edges(p1,p2,size);
    }

    private static void display_edges(Player p1, Player p2, int size) {
	System.out.print(p1.getEdge() + "\\" + p2.getEdge());
	for (int i = 1; i <= size - 2 ; i++) {
	    System.out.print(" " + p2.getEdge());
	}
	System.out.print(" " + p2.getEdge() + "\\" + p1.getEdge() + "\n");
    }

    private static String displayPawn(int pawn) {
	if ( pawn == 1 ) return Game.BLUE;
	else if (pawn == 2) return Game.RED;
	else return Game.WHITE;
    }


    public static boolean undo(Scanner s) {
	System.out.println("Cancel last move ? y/n");
	String str = s.nextLine();
	System.out.println(str);
	char c = str.charAt(0);
	if (c == 'y') {
	    System.out.println("Annulation du dernier coup!");
	    InterfaceAvecC.undo();
	    return true;
	}
	return false;
    }


}

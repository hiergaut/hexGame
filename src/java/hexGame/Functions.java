
/*****************************************************************/
/*								 */
/*			HexGame - Projet			 */
/*			 Functions Class 			 */
/*			Jonathan Lao-Kan			 */
/*			   22 mai 2017				 */
/*								 */
/*****************************************************************/

import java.util.Scanner;

public class Functions {

    private final static int LINES_SEP = 10;
    protected final static String CENTER = "\t\t\t\t\t\t\t\t";
    protected final static String MIDCENTER = "\t\t\t\t\t\t";
    protected final static String SUBCENTER = "\t\t\t\t";
    private final static String BANNER =                                                                                                                                         
 "\u001b[31mhhhhhhh                                                                                                                                         \n"  
+ "h:::::h                                                                                                                                        \n"
+ "h:::::h                                                                                                                                        \n"
+ "h:::::h                                                                                                                                        \n"
+ " h::::h hhhhh           eeeeeeeeeeee  xxxxxxx      xxxxxxx        ggggggggg   ggggg aaaaaaaaaaaaa      mmmmmmm    mmmmmmm       eeeeeeeeeeee    \n"
+ " h::::hh:::::hhh      ee::::::::::::ee x:::::x    x:::::x        g:::::::::ggg::::g a::::::::::::a   mm:::::::m  m:::::::mm   ee::::::::::::ee  \n"
+ " h::::::::::::::hh   e::::::eeeee:::::eex:::::x  x:::::x        g:::::::::::::::::g aaaaaaaaa:::::a m::::::::::mm::::::::::m e::::::eeeee:::::ee\u001b[0m\n"
+ " \u001b[32mh:::::::hhh::::::h e::::::e     e:::::e x:::::xx:::::x        g::::::ggggg::::::gg          a::::a m::::::::::::::::::::::me::::::e     e:::::e\n"
+ " h::::::h   h::::::he:::::::eeeee::::::e  x::::::::::x         g:::::g     g:::::g    aaaaaaa:::::a m:::::mmm::::::mmm:::::me:::::::eeeee::::::e\n"
+ " h:::::h     h:::::he:::::::::::::::::e    x::::::::x          g:::::g     g:::::g  aa::::::::::::a m::::m   m::::m   m::::me:::::::::::::::::e \n"
+ " h:::::h     h:::::he::::::eeeeeeeeeee     x::::::::x          g:::::g     g:::::g a::::aaaa::::::a m::::m   m::::m   m::::me::::::eeeeeeeeeee  \n"
+ " h:::::h     h:::::he:::::::e             x::::::::::x         g::::::g    g:::::ga::::a    a:::::a m::::m   m::::m   m::::me:::::::e           \n"
+ " h:::::h     h:::::he::::::::e           x:::::xx:::::x        g:::::::ggggg:::::ga::::a    a:::::a m::::m   m::::m   m::::me::::::::e          \u001b[0m\n"
+ " \u001b[33mh:::::h     h:::::h e::::::::eeeeeeee  x:::::x  x:::::x        g::::::::::::::::ga:::::aaaa::::::a m::::m   m::::m   m::::m e::::::::eeeeeeee  \n"
+ " h:::::h     h:::::h  ee:::::::::::::e x:::::x    x:::::x        gg::::::::::::::g a::::::::::aa:::am::::m   m::::m   m::::m  ee:::::::::::::e  \n"
+ " hhhhhhh     hhhhhhh    eeeeeeeeeeeeeexxxxxxx      xxxxxxx         gggggggg::::::g  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee  \n"
+ "                                                                           g:::::g                                                              \n"
+ "                                                               gggggg      g:::::g                                                              \n"
+ "                                                               g:::::gg   gg:::::g                                                              \n"
+ "                                                                g::::::ggg:::::::g                    S4 - 2017 PROJECT                         \n"
+ "                                                                 gg:::::::::::::g                                                               \n"
+ "                                                                   ggg::::::ggg                                                                 \n"
+ "                                                                      gggggg      \u001b[0m";

    /**
     * Display the starting menu
     */
    public static void printMenu() {
	System.out.println();
	System.out.println(CENTER + "1. Start");
	System.out.println(CENTER + "2. Load");
	System.out.println(CENTER + "3. Options");
	System.out.println(CENTER + "4. Exit");
	System.out.println();
    }

    /**
     * Display the second menu
     */
    public static void printSubMenu() {
	System.out.println();
	System.out.println(CENTER + "1. 1 Player");
	System.out.println(CENTER + "2. 2 Player");
	System.out.println(CENTER + "3. Return");
	System.out.println();
    }
    /**
     * Clears the console screen
     */
    public static void clearScreen() {  
	System.out.print("\033[H\033[2J");  
	System.out.flush();  
    }  

    /**
     * Display the main banner of the game
     */
    public static void printBanner() {
	System.out.println(BANNER);
    }

    /**
     * Display the player's action menu
     */
    public static void printActionMenu() {
	System.out.println();
	System.out.println(SUBCENTER + "1. Place a pawn \t\t 2. Save the game \t\t 5.End Turn");
	System.out.println(SUBCENTER + "3. Cancel last move \t\t 4. Give up.");
    }
     
    /**
     * Inner function that prints blank lines
     * @param n, the number of lines to print
     */
    protected static void printBlanks(int n) {
	for (int i = 0; i < n; ++i) {
	    System.out.println();
	}
    }

    /**
     * Display overhead infos of current game
     */
    public static void printInfos(Player player) {
	printBlanks(2);
	System.out.printf(SUBCENTER + "Name: %-10s",player.getName());
	System.out.printf("Turn: %-10s",player.getRound());
	System.out.printf("Last action of %s : %-10s", player.getName(), player.getLastMove());
	printBlanks(2);
    }

    /**
     * Display the options menu
     */
    public static void printOptions(Player p1, Player p2) {
	System.out.println();
	System.out.printf(CENTER + "1. Change the size of the Board (Curr : %d)", Game.boardSize);
	System.out.println();
	System.out.printf(CENTER + "2. Change the starting player (Curr : %s)",p1.isStarting ? 
	Game.RED : Game.BLUE );
	System.out.println();
	System.out.println(CENTER + "3. Back");
	printBlanks(2);
    }

    /**
     * Ask the size of the board
     * @param s, the scanner to read I/O
     * @return the size of the board
     */
    public static int askBoardSize(Scanner s) {
	int boardSize;

	System.out.print(CENTER + "Board size: ");
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

	System.out.print(CENTER + "Player " + num + " name : ");
	playerName = s.next();

	return playerName;
    }

    /**
     * Display the current board
     * @param size, the size of the board
     */
    public static void displayBoard(Player p1, Player p2, int size) {
	System.out.print(MIDCENTER);
	display_edges(p1,p2,size);
	for (int i = 0; i < size; i++) {
	    System.out.print(MIDCENTER);
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

	System.out.print(MIDCENTER);
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

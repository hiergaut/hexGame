package hexGame;

import java.util.Scanner;

public class Functions {

    /**
     * Display the starting menu
     */
    public static void printMenu() {
	System.out.println();
	System.out.println("1. Start");
	System.out.println("2. Options");
	System.out.println("3. Quitter");
	System.out.println();
    }

    /**
     * Display the second menu
     */
    public static void printSubMenu() {
	System.out.println();
	System.out.println("1. 1 Joueur");
	System.out.println("2. 2 Joueur");
	System.out.println("3. Back");
	System.out.println();
    }
     
    /**
     * Display overhead infos of game
     */
    public static void printInfos(Player player) {
	System.out.println();
	System.out.printf("Player Name: %-10s",player.getName());
	System.out.printf("Round: %-10s",player.getRound());
	System.out.printf("%s's last move: %-10s", player.getName(), player.getLastMove());
	System.out.println();
	System.out.println();
    }

    /**
     * Display the options menu
     */
    public static void printOptions(Board b, Player p1, Player p2) {
	System.out.println();
	System.out.printf("1. Change the size of the Board (Curr : %d)", b.getSize());
	System.out.println();
	System.out.printf("2. Change the starting player (Curr : %s)",p1.isStarting ? 
	p1.getPawn() : p2.getPawn() );
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


}

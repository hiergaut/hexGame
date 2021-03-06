
/*****************************************************************/
/*								 */
/*			HexGame - Projet			 */
/*			   Game Class   			 */
/*			Jonathan Lao-Kan			 */
/*			   22 mai 2017				 */
/*								 */
/*****************************************************************/

import java.util.*;
import java.io.*;

public abstract class Game {

    protected static int boardSize = 4;
    protected static final String RED = "\u001b[41m  \u001b[0m";
    protected static final String BLUE = "\u001b[44m  \u001b[0m";
    protected static final String WHITE = "\u001b[47m  \u001b[0m";
    private static final int SAVEFILE_NUMBER = 19;
    private static final int BUF_SIZ = 256;
    protected static final String SAVEJ = ".hex";
    protected static final String SAVEG = ".log";


    private static void startGameC(Player p1, Player p2, Scanner s) {
	boolean gameover = false;
	int gameStatus;
	Player starting;
	Player challenger;

	starting = p1.getStartingStatus() ? p1 : p2;
	challenger = p1.getStartingStatus() ? p2 : p1;

	System.out.println(starting.getName() + " starts the game!");
	while (!gameover) {
	    gameover = starting.play(p1,p2,boardSize,s);
	    if (gameover) {
		System.out.println(Functions.CENTER + starting.getName() + " concedes!");
		Functions.tempScreen(s);
		break;
	    }
	    
	    if ( (gameStatus = InterfaceAvecC.hasAWinner()) != 0 ) {
		Functions.clearScreen();
		Functions.printBanner();
		System.out.println(Functions.CENTER + starting.getName() + " wins!" );
		Functions.displayBoard(p1,p2,boardSize);
		Functions.tempScreen(s);
		break;
	    }
	    

	    gameover = challenger.play(p1,p2,boardSize,s);
	    if (gameover) {
		System.out.println(Functions.CENTER + challenger.getName() +" concedes!");
		Functions.tempScreen(s);
		break;
	    }

	    if ( (gameStatus = InterfaceAvecC.hasAWinner()) != 0 ) {
		Functions.clearScreen();
		Functions.printBanner();
		System.out.println(Functions.CENTER + challenger.getName() + " wins!" );
		Functions.displayBoard(p1,p2,boardSize);
		Functions.tempScreen(s);
		break;
	    }
	}
    }

    /**
     * Resume a game from a saved file
     * @param p1, the first player
     * @param p2, the second player
     * @param s, the scanner for I/O
     */ 
    private static void resumeGame(Player p1, Player p2, Scanner s) {
	boolean gameover = false;
	Player starting;
	Player challenger;

	starting = p1.getPlaying() ? p1 : p2;
	challenger = (starting == p1) ? p2 : p1;

	System.out.println(Functions.CENTER + starting.getName() + " resumes the game!");
	while (!gameover) {
	    gameover = starting.play(p1,p2,boardSize,s);
	    if (gameover) {
		System.out.println(Functions.CENTER + starting.getName() + " concedes!");
		Functions.tempScreen(s);
		break;
	    }
	    
	    if ( InterfaceAvecC.hasAWinner() != 0 ) {
		Functions.clearScreen();
		Functions.printBanner();
		System.out.println( Functions.CENTER + starting.getName() + " wins!" );
		Functions.displayBoard(p1,p2,boardSize);
		Functions.tempScreen(s);
		break;
	    }
	    

	    gameover = challenger.play(p1,p2,boardSize,s);
	    if (gameover) {
		System.out.println(Functions.CENTER + challenger.getName() +" concedes!");
		Functions.tempScreen(s);
		break;
	    }

	    if ( InterfaceAvecC.hasAWinner() != 0 ) {
		Functions.clearScreen();
		Functions.printBanner();
		System.out.println(Functions.CENTER + challenger.getName() + " wins!" );
		Functions.displayBoard(p1,p2,boardSize);
		Functions.tempScreen(s);
		break;
	    }
	}
    }
    
    /**
     * Load a previous game
     * @param s, the scanner for I/O
     */
    private static void loadGame(Player p1, Player p2,AI comp,Scanner s) {
	Functions.printBlanks(1);
	System.out.print(Functions.CENTER + "Name of file to load : ");
	String filename = s.nextLine();

	String[] lines = new String[SAVEFILE_NUMBER];
	try {
	    File file = new File("file/saves/" + filename + Game.SAVEJ);
	    file.getParentFile().mkdirs();

	    FileReader r = new FileReader(file);
	    char[] buffer = new char[BUF_SIZ];
	    System.out.println(r.read(buffer));
	    Arrays.fill(lines,"");

	    int i = 0;
	    for (char c : buffer) {
		if (c != '\n') {
		    lines[i] = lines[i] + c;
		}
		else {
		    i++;
		}
	    }

	    Game.boardSize = Integer.parseInt(lines[0]);
	    int gameId = Integer.parseInt(lines[1]);
	    System.out.println(gameId);
	    Player challenger = loadInfos(p1,p2,comp,lines);
	    InterfaceAvecC.restoreGame(gameId,"file/saves/" + filename+SAVEG);
	    r.close();
	    resumeGame(p1,challenger,s);
	}
	catch (Exception e) {
	    e.printStackTrace();
	}
    }

    /**
     * Load player's info to a textfile
     * @param p1, the first player (Always Human)
     * @param p2, the second player (Human or CPU)
     * @param b, the buffer from which to retrieve infos
     * @return the challenger player of the saved state
     */
    private static Player loadInfos(Player p1, Player p2, AI comp, String[] buffer) {
	// Player 1 infos
	p1.setName(buffer[2]);
	p1.setPawn(Integer.parseInt((buffer[3])));
	p1.setEdge(buffer[4]);
	p1.setRound(Integer.parseInt(buffer[5]));
	p1.setHasPlayed(Boolean.parseBoolean(buffer[6]));
	p1.setLastMove(buffer[7]);
	p1.setStartingStatus(Boolean.parseBoolean(buffer[8]));
	p1.setPlaying(Boolean.parseBoolean(buffer[9]));
	
	// Player 2 or CPU infos
	if (buffer[10].equals("Computer")) {
	    comp.setName(buffer[10]);
	    comp.setPawn(Integer.parseInt((buffer[11])));
	    comp.setEdge(buffer[12]);
	    comp.setRound(Integer.parseInt(buffer[13]));
	    comp.setHasPlayed(Boolean.parseBoolean(buffer[14]));
	    comp.setLastMove(buffer[15]);
	    comp.setStartingStatus(Boolean.parseBoolean(buffer[16]));
	    return comp;
	}
	else {
	    p2.setName(buffer[10]);
	    p2.setPawn(Integer.parseInt((buffer[11])));
	    p2.setEdge(buffer[12]);
	    p2.setRound(Integer.parseInt(buffer[13]));
	    p2.setHasPlayed(Boolean.parseBoolean(buffer[14]));
	    p2.setLastMove(buffer[15]);
	    p2.setStartingStatus(Boolean.parseBoolean(buffer[16]));
	    return p2;
	}
    }

    public static void main(String[] args) {
	Scanner scan = new Scanner(System.in);
	Player p1 = new Player(1,BLUE);
	Player p2 = new Player(2,RED);
	AI comp = new AI(2,RED);
	boolean wantsToQuit = false;



	while (!wantsToQuit) {
	    Functions.clearScreen();
	    Functions.printBanner();
	    Functions.printMenu();
	    int choice = 0;

	    choice = Functions.checkInput(scan);
	    switch ( choice ) {
		case 1:
		    InterfaceAvecC.newGame(boardSize);
		    Functions.clearScreen();
		    Functions.printBanner();
		    Functions.printSubMenu();
		    choice = Functions.checkInput(scan);
		    switch ( choice )  {
			case 1:
			    Functions.clearScreen();
			    Functions.printBanner();
			    Functions.printBlanks(1);
			    System.out.println(Functions.CENTER + "Human vs AI ! ");
			    p1.setName(Functions.askPlayerName(1,scan));
			    startGameC(p1,comp,scan);
			    InterfaceAvecC.endGame();
			    break;
			case 2:
			    Functions.clearScreen();
			    Functions.printBanner();
			    Functions.printBlanks(1);
			    System.out.println(Functions.CENTER + "Human vs Human ! ");
			    p1.setName(Functions.askPlayerName(1,scan));
			    p2.setName(Functions.askPlayerName(2,scan));
			    startGameC(p1,p2,scan);
			    InterfaceAvecC.endGame();
			    break;
			case 3:
			    InterfaceAvecC.endGame();
			    break; 
			default:
			    InterfaceAvecC.endGame();
			    break;
		    }
		    break;
		case 2:
		    Functions.clearScreen();
		    Functions.printBanner();
		    loadGame(p1,p2,comp,scan);
		    InterfaceAvecC.endGame();
		    break;
		case 3:
		    Functions.clearScreen();
		    Functions.printBanner();
		    Functions.printBlanks(1);
		    System.out.println(Functions.CENTER + "Options");
		    Functions.printOptions(p1,p2);
		    choice = Functions.checkInput(scan);
		    switch ( choice ) {
			case 1:
			    boardSize = Functions.askBoardSize(scan);
			    InterfaceAvecC.newGame(boardSize);
			    Functions.clearScreen();
			    Functions.printBanner();
			    Functions.printBlanks(2);
			    System.out.println(Functions.CENTER + "Change Successfull !");
			    Functions.tempScreen(scan);
			    break;
			case 2:
			    p1.switchStarting();
			    Functions.clearScreen();
			    Functions.printBanner();
			    Functions.printBlanks(2);
			    System.out.println(Functions.CENTER + "Change Successfull !");
			    Functions.tempScreen(scan);
			    break;
			case 3:
			    break; 
			default:
			    Functions.clearScreen();
			    Functions.printBanner();
			    Functions.printBlanks(2);
			    System.out.println("Invalid choice");
			    break;
		    }
		    break;
		case 4:
		    Functions.clearScreen();
		    Functions.printBanner();
		    System.out.println(Functions.CENTER + "Goodbye !");
		    wantsToQuit = true;
		    break;
		default:
		    InterfaceAvecC.endGame();
		    break;
	    }
	}

	scan.close();
    }
}


public class Main {
    public static void main(String args[]) {
	final boolean BLACK =true;

	InterfaceAvecC.newGame(5);

	if (InterfaceAvecC.permission(2, 4))
	    System.out.println("Oh yeah");

	InterfaceAvecC.setPawn(InterfaceAvecC.WHITE_PAWN, 2, 4);

	if (InterfaceAvecC.hasAWinner() !=0)
	    System.out.println("Winner");

	InterfaceAvecC.saveGame();
	InterfaceAvecC.restoreGame(5);
	InterfaceAvecC.undo();

	InterfaceAvecC.displayHistoryGame();
	InterfaceAvecC.getPawn(3, 5);

	InterfaceAvecC.displayGraphGame();
	InterfaceAvecC.displayPlateau();
	InterfaceAvecC.displayGroup(InterfaceAvecC.BLACK_PAWN);

	InterfaceAvecC.endGame();

    }
}

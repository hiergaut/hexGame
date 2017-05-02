// import java.util.Scanner;

public class Main {
    public static void main(String args[]) {

        InterfaceAvecC.newGame(6);
        InterfaceAvecC.insertPawn(InterfaceAvecC.BLACK_PAWN, 2, 2);
        InterfaceAvecC.insertPawn(InterfaceAvecC.WHITE_PAWN, 3, 2);

        // Scanner reader = new Scanner(System.in);  // Reading from System.in
        // System.out.println("Enter a number: ");
        // int n = reader.nextInt(); // Scans the next token of the input as an int.

        InterfaceAvecC.insertPawn(InterfaceAvecC.WHITE_PAWN, 2, 4);

        if (InterfaceAvecC.hasAWinner() ==0)
            System.out.println("no Winner");

        InterfaceAvecC.saveGame();
        InterfaceAvecC.restoreGame(5);
        // InterfaceAvecC.undo();

        InterfaceAvecC.displayHistoryGame();
        InterfaceAvecC.getPawn(3, 5);

        // InterfaceAvecC.displayGraphGame();
        // InterfaceAvecC.displayPlateau();
        // InterfaceAvecC.displayGroup(InterfaceAvecC.BLACK_PAWN);

        InterfaceAvecC.endGame();

    }
}

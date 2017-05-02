// import java.util.Scanner;

public class Main {
    static public void aff(int side) {
        for (int l =0; l <side; l++) {
            for (int c =0; c <side; c++) {
                System.out.print(InterfaceAvecC.getPawn(l, c));
            }
            System.out.println();
        }
        System.out.println("winner =" +InterfaceAvecC.hasAWinner());
        System.out.println("----------------------------------------------------");
    }

    public static void main(String args[]) {

        int side =2;


        InterfaceAvecC.newGame(side);
        aff(side);
        InterfaceAvecC.insertPawn(InterfaceAvecC.BLACK_PAWN, 0, 0);
        aff(side);
        InterfaceAvecC.insertPawn(InterfaceAvecC.WHITE_PAWN, 1, 1);
        aff(side);
        InterfaceAvecC.insertPawn(InterfaceAvecC.WHITE_PAWN, 0, 1);
        aff(side);
        InterfaceAvecC.undo();
        aff(side);
        InterfaceAvecC.insertPawn(InterfaceAvecC.BLACK_PAWN, 0, 1);
        aff(side);

        // Scanner reader = new Scanner(System.in);  // Reading from System.in
        // System.out.println("Enter a number: ");
        // int n = reader.nextInt(); // Scans the next token of the input as an int.



        InterfaceAvecC.saveGame();
        InterfaceAvecC.restoreGame(5);
        // InterfaceAvecC.undo();

        InterfaceAvecC.displayHistoryGame();

        // InterfaceAvecC.displayGraphGame();
        // InterfaceAvecC.displayPlateau();
        // InterfaceAvecC.displayGroup(InterfaceAvecC.BLACK_PAWN);

        InterfaceAvecC.endGame();

    }
}

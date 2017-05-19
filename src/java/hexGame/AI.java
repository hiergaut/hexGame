import java.util.Scanner;

class AI extends Player {

    /**
     * Constructor of AI Class
     * @param pawn, the pawn the AI will use
     * @param edge, the edges the AI need to link to win
     */
    public AI(int pawn, String edge) {
	super(pawn,edge);
	setName("Computer");
    }

    /**
     * Simple wrapper for AI's play method
     */
    @Override
    public void play(Scanner s) {
	InterfaceAvecC.botTakePlace(getPawn());
	incRound();
    }

}

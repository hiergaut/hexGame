
/*****************************************************************/
/*								 */
/*			HexGame - Projet			 */
/*			    AI Class	 			 */
/*			Jonathan Lao-Kan			 */
/*			   18 mai 2017				 */
/*								 */
/*****************************************************************/

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
    public boolean play(Player p1, Player p2, int size, Scanner s) {
	InterfaceAvecC.botTakePlace(getPawn());
	incRound();
	return false;
    }

}

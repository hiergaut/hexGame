package hexGame;

public class Functions {

    public static void print_menu() {
	System.out.println("1. Start");
	System.out.println("2. Options");
    }
     
    public static void print_infos(Player player) {
	System.out.print("Player Name: ");
	System.out.println(player.getName());
	System.out.print("Round: ");
	System.out.println(player.getRound());
	System.out.print("Last Move: ");
	System.out.println(player.getLastMove());
	System.out.println();
    }


}

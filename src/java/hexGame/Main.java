
class Main {
	public static void main(String args[]) {
		int n =11;
		Joueur j1 =new Joueur("gauthier" ,'*' ,'B');
		Joueur j2 =new Joueur("florent" ,'o' ,'W');
		Plateau p =new Plateau(n ,n ,j1 ,j2);
		p.display();

	}
}

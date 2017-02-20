
class Plateau {
	protected int width;
	protected int length;
	protected Case m[][];
	protected Joueur j1;
	protected Joueur j2;

	Plateau(int width ,int length ,Joueur j1 ,Joueur j2) {
		this.width =width;
		this.length =length;
		this.m =new Case[width][length];
		this.j1 =j1;
		this.j2 =j2;
		this.init();
	}

	private void init() {
		for (int i =0 ;i <this.width ;i++) {
			for (int j =0 ;j <this.length ;j++) {
				m[i][j] =new Case();
			}
		}
	}

	void display() {
		System.out.print(j2.getEdge());
		for (int i =1 ;i <=this.length ;i++) {
			System.out.print(" " +j2.getEdge());
		}
		System.out.print("\\" +j1.getEdge() +"\n");

		for (int i =0 ;i <this.width ;i++) {
			for (int j =0 ;j <=i ;j++)
				System.out.print(" ");

			System.out.print(j1.getEdge());
			for (int j =0 ;j <this.length ;j++) {
				System.out.print(" " +m[i][j].toString());
			}
			System.out.print(" ");
			System.out.print(j1.getEdge());
			System.out.println();
		}

		for (int i =0 ;i <this.width ;i++) {
			System.out.print(" ");
		}
		
	}
}


class Plateau {
	protected int width;
	protected int length;
	protected Case m[][];

	Plateau(int width ,int length) {
		this.width =width;
		this.length =length;
		this.m =new Case[width][length];
		init();
	}

	private void init() {
		for (int i =0 ;i <this.width ;i++) {
			for (int j =0 ;j <this.length ;j++) {
				m[i][j] =new Case();
			}
		}
	}

	void display() {
		for (int i =0 ;i <this.width ;i++) {
			for (int j =0 ;j <this.length ;j++) {
				System.out.print(m[i][j].toString());
			}
			System.out.println();
		}
	}
}

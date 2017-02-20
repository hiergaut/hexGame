
class Joueur {
	protected String nom;
	protected char pion;
	protected char edge;

	Joueur(String nom ,char pion ,char edge) {
		this.nom =nom;
		this.pion =pion;
		this.edge =edge;
	}

	char getEdge() {
		return this.edge;
	}

}

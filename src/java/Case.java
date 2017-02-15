
class Case {
	protected boolean empty;
	protected boolean leftPlayer;

	Case() {
		this.empty =true;
	}

	public String toString() {
		if (this.empty) {
			return ".";
		}
		return "a";
	}
}

public class Prisoner {
	
	public String gameStatus;
	public String token;
	public int remaining;
	public String state;
	
	public String toString(){
		return "'status': " + gameStatus + ", 'token': " + token + ", 'remaining_guesses': " + remaining + ", 'state': " + state;
	}
}

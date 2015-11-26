//runs the game of Hangman
public class HangmanRunner {
	public static void main(String[] args){
		HangmanAI intelligence = new HangmanAI();
		Prisoner hostage = JailWeb.startGame();
		int numError = 0;
		int numGuess = 0;
		while(hostage.gameStatus.equals("ALIVE")){
			System.out.println(hostage.state);
			char guess = intelligence.makeGuess(hostage.state); //get a guess using AI
			Prisoner hostage_after = JailWeb.makeGuess(hostage, guess); //Update the state
			numGuess++;
			if(hostage.state.equals(hostage_after.state)){
				intelligence.update(guess, false);
				if(hostage_after.remaining == 1){
					System.out.println(guess + " is " + false + " , " + hostage_after.remaining + " more try.");
				}
				else{
					System.out.println(guess + " is " + false + " , " + hostage_after.remaining + " more tries.");
				}
				numError++;
			}
			else{
				intelligence.update(guess, true);
				System.out.println(guess + " is " + true);
			}
			hostage = hostage_after;
		}
		if(hostage.gameStatus.equals("DEAD")){
			System.out.println(hostage.state);
			System.out.println("Mission Unsuccessful!");
		}
		if(hostage.gameStatus.equals("FREE")){
			System.out.println(hostage.state);
			System.out.println("Mission Accomplished!");
		}
	}
}

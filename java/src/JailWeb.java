import java.io.BufferedReader;
import java.io.IOException;
import java.net.URL;
import java.util.regex.Matcher;
import java.io.InputStreamReader;
import java.util.regex.*;

//Get the state from the website
public class JailWeb {
	public static Prisoner playGame(String s){
		Prisoner prisoner = new Prisoner();
		try{
			BufferedReader in = new BufferedReader(new InputStreamReader(
					new URL("http://gallows.hulu.com/play?code=kvasukib@ucsd.edu" + s).openStream()));
			String info = in.readLine(); 

			Pattern p = Pattern.compile("(ALIVE|DEAD|FREE)"); // get the status
			Matcher m = p.matcher(info);

			Pattern p1 = Pattern.compile("(\\d+)"); //get the token
			Matcher m1 = p1.matcher(info);

			
			Pattern p2 = Pattern.compile("(\\d)(,)"); //get remaining guesses
			Matcher m2 = p2.matcher(info);
			
			Pattern p3 = Pattern.compile("([A-Z_'\\s]+)(\"})"); //get state
			Matcher m3 = p3.matcher(info);

			
			if(m.find() && m1.find() && m2.find() && m3.find()){
				prisoner.gameStatus = m.group();
				prisoner.token = m1.group();
				prisoner.remaining = Integer.parseInt(m2.group(1));
				prisoner.state = m3.group(1);
			}
		}catch(IOException e){
			System.err.println(e);
		}
		return prisoner;
	}
	//start a new game
	public static Prisoner startGame(){
		return playGame("");
	}
	//continue until the prisoner is dead
	public static Prisoner makeGuess(Prisoner hostage, char guess){
		return playGame(String.format("&token=%s&guess=%s", hostage.token, guess));
	}
}

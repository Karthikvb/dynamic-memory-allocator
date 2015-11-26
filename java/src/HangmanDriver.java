import java.io.*;
import java.net.*;
import java.util.*;
import java.util.regex.*;

class prisoner {
	
	public String gStatus;
	public String token;
	public int rem;
	public String state;
	
   public prisoner(String a, String b, int c, String d) {
     gStatus = a;
     token = b;
     rem = c;
     state = d;
   }
	public String toString() {
		return "'status': " + gStatus + ", 'token': " + token + ", 'remaining_guesses': " + rem + ", 'state': " + state;
	}
}

class webParse {
  public static prisoner play(String s) {
    prisoner pr = null;
    try {
      BufferedReader br = new BufferedReader(new InputStreamReader(new URL("http://gallows.hulu.com/play?code=kvasukib@ucsd.edu" + s).openStream()));
      String input = br.readLine();
      Pattern p = Pattern.compile("ALIVE|DEAD|FREE");
      Matcher m0 = p.matcher(input);
      p = Pattern.compile("(\\d+)");
      Matcher m1 = p.matcher(input);
      p = Pattern.compile("(\\d)(,)");
      Matcher m2 = p.matcher(input);
      p = Pattern.compile("([A-Z_'\\s]+)(\"})");
      Matcher m3 = p.matcher(input);
      
      if (m0.find() && m1.find() && m2.find() && m3.find()) {
        pr = new prisoner(m0.group(), m1.group(), Integer.parseInt(m2.group(1)), m3.group(1));
      }
    } catch(Exception e) {
      System.out.println(e);
    }
    return pr;
  }
  
  public static prisoner start(){
    return play("");
  }
  
  public static prisoner guess(prisoner hostage, char guess){
    return play(String.format("&token=%s&guess=%s", hostage.token, guess));
  }
}

class game {

	private Map<Integer, List<String>> wordList = new HashMap<Integer, List<String>>();
	private Set<Character> correct = new HashSet<Character>();
	private Set<Character> incorrect = new HashSet<Character>();

	game() {
		try {
			for (File f : new File("dict/").listFiles()) {
				BufferedReader reader = new BufferedReader(new FileReader(f));
				for (String str; (str = reader.readLine()) != null;) {
					str = str.trim();
					if (!wordList.containsKey(str.length())) {
						wordList.put(str.length(), new ArrayList<String>());
					}
					wordList.get(str.length()).add(str);
				}
			}
		} catch (IOException e) {
			System.err.println(e);
		}

	}

	public char makeGuess(String state) {
		List<String> state_list = new ArrayList<String>(Arrays.asList(state
				.split("[^A-Z_']+")));
		StringBuilder excluding = new StringBuilder();
		for (Iterator<Character> ex = incorrect.iterator(); ex.hasNext();) {
			excluding.append(ex.next());
		}
		List<String> possibleWords = new ArrayList<String>();

		int count = 0;
		String guessing = null;
		int underscore_counter = 100;
		for (String word : state_list) {
			for (int i = 0; i < word.length(); i++) {
				if ("_".equals(word.charAt(i))) {
					underscore_counter--;
				}
			}
			if (underscore_counter > count) {
				guessing = word;
				count = underscore_counter;
				underscore_counter = 100;
			}
		}
		if(guessing.length() == 1){
			return (!correct.contains('a') && !incorrect.contains('a')) ? 'a' : 'I';
		}
		String word = guessing.toLowerCase();
		Pattern regex = Pattern.compile(word.replace(
				"_",
				(excluding.length() > 0) ? String.format("[a-z&&[^%s]]",
						excluding) : "[a-z]"));
		if (wordList.containsKey(word.length())) {
			for (String guess : wordList.get(word.length())) {
				Matcher match = regex.matcher(guess);
				if (match.find()) {
					possibleWords.add(guess);
				}
			}
		}
		Map<Character, Integer> frequency = new HashMap<Character, Integer>();
		for (String possible : possibleWords) {
			Set<String> letters = new HashSet<String>();
			for (char letter : possible.toCharArray()) {
				if (!letters.contains(letter)) {
					if (!frequency.containsKey(letter)) {
						frequency.put(letter, 1);
					} else {
						frequency.put(letter, frequency.get(letter) + 1);
					}
				}
			}
		}
		char guessLetter = 'a';
		int freq = 0;
		boolean no_letter = true;
		for (char c = 'a'; c <= 'z'; c++) {
			if (!correct.contains(c) && !incorrect.contains(c)) {
				if (frequency.get(c) != null && frequency.get(c) > freq) {
					guessLetter = c;
					freq = frequency.get(c);
					no_letter = false;
				}
			}
		}
		if (no_letter) {
			for (char c = 'a'; c <= 'z'; ++c) {
				if (!(correct.contains(c) || incorrect.contains(c))) {
					return c;
				}
			}
		}
		return guessLetter;
	}

	public void update(char guess, boolean success) {
		if (success) {
			correct.add(guess);
		} else {
			incorrect.add(guess);
		}
	}
}

public class HangmanDriver {
	public static void main(String[] args){
		game intelligence = new game();
		prisoner hostage = webParse.start();
		int numError = 0, numGuess = 0;
		while(hostage.gStatus.equals("ALIVE")){
			System.out.println("State of Prisoner: " + hostage.state);
			char guess = intelligence.makeGuess(hostage.state);
			prisoner hostage_after = webParse.guess(hostage, guess);
			numGuess++;
			if(hostage.state.equals(hostage_after.state)){
				intelligence.update(guess, false);
				if(hostage_after.rem == 1){
					System.out.println(guess + " is " + false + " , " + hostage_after.rem + " try left.");
				}
				else{
					System.out.println(guess + " is " + false + " , " + hostage_after.rem + " tries left.");
				}
				numError++;
			}
			else{
				intelligence.update(guess, true);
				System.out.println(guess + " is " + true);
			}
			hostage = hostage_after;
		}
		if(hostage.gStatus.equals("DEAD")){
			System.out.println(hostage.state);
			System.out.println("Prisoner dead. Prediction failed!");
		}
		if(hostage.gStatus.equals("FREE")){
			System.out.println(hostage.state);
			System.out.println("Prisoner freed. Prediction succeeded!");
		}
	}
}

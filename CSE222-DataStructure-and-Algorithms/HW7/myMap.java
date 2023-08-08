import java.util.LinkedHashMap;
import java.util.ArrayList;

public class myMap {
	LinkedHashMap <String, info> map;
	int mapSize;
	String str;
	String [] words;


	/**
	 * Constructs a new instance of the myMap class.
	 * Initializes the map as a LinkedHashMap, sets the map size to 0,
	 * and initializes the str and words variables as null.
	 */
	public myMap() 
	{
		this.map = new LinkedHashMap<String, info>();
		this.mapSize = 0;
		this.str = null;
		this.words = null;
	}
	/**
	 * Appends a word to the information associated with the given character in the map.
	 * If the character already exists in the map, the word is pushed to the existing information.
	 * If the character does not exist in the map, a new character and its associated information are added.
	 *
	 * @param x    the character to append the word to
	 * @param word the word to be appended
	 */
	public void append(String x, String word) 
	{
		if (this.map.containsKey(x)) 
		{
			info myinfo = this.map.get(x);
			myinfo.push(word);
		}
		else
			addNewCharacter(x, word);
	}
	/**
	 * Adds a new character and its associated information to the map.
	 *
	 * @param x    the character to be added
	 * @param word the word to be associated with the character
	 */
	private void addNewCharacter (String x, String word) 
	{
		ArrayList<String> words = new ArrayList<String>();
		words.add(word);
		info myInfo = new info (1, words);
		this.map.put(x, myInfo);
		this.mapSize ++;
	}

	/**
	 * Assigns a list of words to the given character in the map.
	 *
	 * @param x     the character to assign the words to
	 * @param words the list of words to be assigned
	 */
	
	public void assign(String x, ArrayList<String> words) 
	{
		addNewCharacter(x, (String) words.get(0));
		for (int i = 1; i < words.size(); i++) 
		{
			append(x, (String) words.get(i));
		}
	}
	/**
	 * Builds the map using the given string.
	 * @param str the string to build the map from
	 */
	public void buildMap (String str) 
	{

		if(str.isEmpty())
        {
            System.out.println("String is empty.\n");
            this.str = null;
            return;
        }
        if(str.matches(".*[a-zA-Z].*") == false)
        {
            System.out.println("String has any letter\n");
            this.str = null;
            return;
        }
		this.str = str.replaceAll("[^a-zA-Z\\s]", "").toLowerCase();

		this.words = this.str.split(" ");

		for (int i = 0; i < this.words.length; i++) 
		{
			for (int j = 0; j < this.words[i].length(); j++) 
			{
				append(this.words[i].substring(j, j + 1), this.words[i]);
			}
		}
	}
	
}

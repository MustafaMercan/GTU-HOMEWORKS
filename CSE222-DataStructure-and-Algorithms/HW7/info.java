import java.util.ArrayList;

public class info {
	int count;
	ArrayList<String> words = new ArrayList<String>();

	public info(int count, ArrayList<String> words) {
		this.count = count;
		this.words = words;
	}
	
	public void push(String word) {
		this.count++;
		this.words.add(word);
	}
	
	// pop wasn't a part of the homework 
	public void pop(String word) {
		if (this.words.contains(word)) {
			this.words.remove(word);
			this.count++;
		}
		else
			System.out.println("'" + word + "' is not found.");
	}
}

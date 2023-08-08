import java.util.LinkedHashMap;
import java.util.Map;
public class myMap{
    LinkedHashMap<Character, info> myLinkedHashMap;
    int mapSize;
    String str;

    /**
     * This constructor method first transforms the given string input into the desired format and then converts it into a map
     * @param input It takes string input
     */
    public myMap(String input)
    {
        System.out.println("Original String -> " + input);
        
        if(input.isEmpty())
        {
            System.out.println("String is empty.\n");
            str = null;
            return;
        }
        if(input.matches(".*[a-zA-Z].*") == false)
        {
            System.out.println("String has any letter\n");
            str = null;
            return;
        }

        this.myLinkedHashMap = new LinkedHashMap<Character, info>();
        this.mapSize = 0;
        
        this.str = input.replaceAll("[^a-zA-Z\\s]", "").toLowerCase();
        
        System.out.println("Preprocessed String -> " + this.str +"\n\n");

        this.create_map();

        this.mapSize = myLinkedHashMap.size();

        System.out.println("The Original (Unsorted) map: ");
        this.print_map();
    }
    /**
     * This constructor method creates an empty object
     */
    public myMap()
    {
        this.myLinkedHashMap = new LinkedHashMap<Character, info>();
        this.mapSize = 0;
        this.str = null;
    }
    /**
     * This constructor method converts the given string expression into a map format by correctly splitting it into separate parts
     */
    public void create_map()
    {
        String[] tmp = this.str.split(" ");
        if(tmp == null)
            return;
        
        for(String element : tmp)
        {
            for(char ch : element.toCharArray())
            {
                if(!this.myLinkedHashMap.containsKey(ch))
                {
                    info tmp_info = new info();
                    tmp_info.add_word(element);
                    this.myLinkedHashMap.put(ch,tmp_info);
                }
                else
                {
                    this.myLinkedHashMap.get(ch).add_word(element);
                }
            }
        }

    }
    /**
     * It adds a new data entry to the map.
     * @param key
     * @param value
     */
    public void add_element(Character key, info value)
    {
        this.myLinkedHashMap.put(key,value);
        this.mapSize = this.myLinkedHashMap.size();
    }
    /**
     * It removes an element from the map
     * @param key The key of the value to be removed
     */
    public void remove_element(Character key)
    {
        this.myLinkedHashMap.remove(key);
        this.mapSize = this.myLinkedHashMap.size();
    }
    /**
     * It returns map
     */
    public LinkedHashMap <Character, info> get_hash_map()
    {
        return this.myLinkedHashMap;
    }
    /**
     * It prints map
     */
    public void print_map() 
    {
        for (Character key : this.myLinkedHashMap.keySet()) 
        {
            info value = this.myLinkedHashMap.get(key);

            System.out.print("Letter: " + key + " - " + "-> ");
            value.print_info();
            System.out.print("\n");
        }
    }
    /**
     * It adds all the data from the input to the map.
     * @param put_all The myMap value to be added to the map.
     */
    public void put_all(myMap added)
    {
        this.myLinkedHashMap.putAll(added.get_hash_map());
        this.mapSize = this.myLinkedHashMap.size();
    }
    /**
     * it returns map size
     */
    public int get_size()
    {
        return this.myLinkedHashMap.size();
    }

}
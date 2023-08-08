import java.util.ArrayList;
public class info{
    int count;
    ArrayList<String> myArrayList;
    /**
     * it initialize empty array list and count
     */
    public info()
    {
        this.myArrayList = new ArrayList<String>();
        this.count = 0 ;
    }
    /**
     * it add new element to arrayList
     * @param word holds new element
     */
    public void add_word(String word)
    {
        myArrayList.add(word);
        count++;
    }
    /**
     * It prints myArrayList 
     */
    public void print_info()
    {
        System.out.print("Count: " + this.count + " - Words: [");
        
        for (int i = 0; i < myArrayList.size(); i++) 
        {
            System.out.print(myArrayList.get(i));
            if(i != myArrayList.size() - 1)
            {
                System.out.print(" , ");
            }
        }
        System.out.println("]");
    }
    /**
     * it returns count value
     */
    public int get_count()
    {
        return this.count;
    }
}
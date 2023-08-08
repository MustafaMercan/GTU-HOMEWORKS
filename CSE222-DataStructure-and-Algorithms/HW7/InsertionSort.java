import java.util.List;
import java.util.ArrayList;
import java.util.Map;

public class InsertionSort {
    myMap originalMap;
    myMap sortedMap;
    List<String> aux;

    /**
     * Constructs a InsertionSort object with the given original map.
     *
     * @param originalMap the original map containing the data to be sorted
     */
    public InsertionSort(myMap originalMap) 
    {
        this.originalMap = originalMap;
        this.aux = new ArrayList<String>(this.originalMap.map.keySet());
        this.sortedMap = new myMap();
    }
    /**
     * Sorts the array using the Insertion Sort algorithm.
     */
    private void insertionSort() 
    {
        int n = aux.size();
        for (int i = 1; i < n; i++) 
        {
            String key = aux.get(i);
            int j = i - 1;
            while (j >= 0 && compareKeys(aux.get(j), key) > 0) 
            {
                aux.set(j + 1, aux.get(j));
                j--;
            }
            aux.set(j + 1, key);
        }
    }
    /**
     * Compares the keys based on their associated count values in the original map.
     *
     * @param key1 the first key to compare
     * @param key2 the second key to compare
     * @return 1 if the count of key1 is greater than the count of key2, -1 otherwise
     */
    private int compareKeys(String key1, String key2) 
    {
        int count1 = originalMap.map.get(key1).count;
        int count2 = originalMap.map.get(key2).count;

        if (count1 > count2) 
        {
            return 1;
        }
        return -1;

    }
    /**
     * Generates a new map by assigning the words associated with each key in the sorted order.
     * The words are retrieved from the original map and assigned to the corresponding keys in the sorted map.
     */
    private void generateNewMap() 
    {
        for (int i = 0; i < aux.size(); i++)
        {
            this.sortedMap.assign(aux.get(i), this.originalMap.map.get(aux.get(i)).words);
        }
    }
    /**
     * Sorts the original map using the insertion sort algorithm.
     */
    public void sort() 
    {
        long startTime = System.nanoTime();
        insertionSort();
        long endTime = System.nanoTime();

        System.out.println("Insertion Sort execution time: " + (endTime - startTime) + " nanoseconds.");
        generateNewMap();
    }
    /**
     * Prints the sorted map
     */
    public void printSortedArray() 
    {
        for (Map.Entry<String, info> e : sortedMap.map.entrySet())
        {
            System.out.println("Letter: " + e.getKey() + " - Count: " + e.getValue().count + " - Words: " + e.getValue().words);
        }       
    }
    /**
     * Prints the original map
     */
    public void printOriginalArray() 
    {
        for (Map.Entry<String, info> e : originalMap.map.entrySet())
        {
            System.out.println("Letter: " + e.getKey() + " - Count: " + e.getValue().count + " - Words: " + e.getValue().words);
        }             
    }
}

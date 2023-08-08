import java.util.List;
import java.util.ArrayList;
import java.util.Map;

public class QuickSort {
    myMap originalMap;
    myMap sortedMap;
    List<String> aux;
    /**
     * Constructs a QuickSort object with the given original map.
     *
     * @param originalMap the original map containing the data to be sorted
     */
    public QuickSort(myMap originalMap) 
    {
        this.originalMap = originalMap;
        this.aux = new ArrayList<String>(this.originalMap.map.keySet());
        this.sortedMap = new myMap();
    }
    /**
     * Sorts the array using the Quick Sort algorithm.
     *
     * @param low  the starting index of the subarray to be sorted
     * @param high the ending index of the subarray to be sorted
     */
    private void quickSort(int low, int high) 
    {
        if (low < high) 
        {
            int pivotIndex = partition(low, high);
            quickSort(low, pivotIndex - 1);
            quickSort(pivotIndex + 1, high);
        }
    }
    /**
     * Partitions the array for the Quick Sort algorithm.
     *
     * @param low  the starting index of the subarray to be partitioned
     * @param high the ending index of the subarray to be partitioned
     * @return the index of the pivot element
     */
    private int partition(int low, int high) 
    {
        String pivot = aux.get(high);
        int i = low - 1;

        for (int j = low; j < high; j++) 
        {
            if (compareKeys(aux.get(j), pivot) <= 0) 
            {
                i++;
                swap(i, j);
            }
        }

        swap(i + 1, high);
        return i + 1;
    }
    /**
     * Swaps the elements at the specified index in the aux list.
     *
     * @param i the index of the first element to swap
     * @param j the index of the second element to swap
     */
    private void swap(int i, int j) 
    {
        String temp = aux.get(i);
        aux.set(i, aux.get(j));
        aux.set(j, temp);
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
        if (count1 < count2) 
        {
            return -1;
        } 
        else if (count1 > count2) 
        {
            return 1;
        } 
        else 
        {
            return key1.compareTo(key2);
        }
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
     * Sorts the original map using the quick sort algorithm.
     */
    public void sort() 
    {
        long startTime = System.nanoTime();

        
        quickSort(0, aux.size() - 1);
        
        long endTime = System.nanoTime();

        System.out.println("Quick Sort execution time: " + (endTime - startTime) + " nanoseconds.");
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
            System.out.println("Letter: " + e.getKey() + " - Count: "  + e.getValue().count + " - Words: " + e.getValue().words);
        }
            
    }
}

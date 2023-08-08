import java.util.List;
import java.util.ArrayList;
import java.util.Map;

public class SelectionSort {
    myMap originalMap;
    myMap sortedMap;
    List<String> aux;
    /**
     * Constructs a SelectionSort object with the given original map.
     *
     * @param originalMap the original map containing the data to be sorted
     */
    public SelectionSort(myMap originalMap) 
    {
        this.originalMap = originalMap;
        this.aux = new ArrayList<String>(this.originalMap.map.keySet());
        this.sortedMap = new myMap();
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
     * Sorts the auxiliary list using the Selection Sort algorithm based on the count values and lexicographical order of the keys.
     * The original map's data is accessed to compare the count values and keys.
     */
    private void selectionSort() 
    {
        int n = aux.size();
        for (int i = 0; i < n - 1; i++) 
        {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) 
            {
                int count1 = originalMap.map.get(aux.get(j)).count;
                int count2 = originalMap.map.get(aux.get(minIndex)).count;
                if (count1 < count2 || (count1 == count2 && aux.get(j).compareTo(aux.get(minIndex)) < 0)) 
                {
                    minIndex = j;
                }
            }
            swap(i, minIndex);
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
     * Sorts the original map using the selection sort algorithm.
     */
    public void sort() 
    {
        long startTime = System.nanoTime();

        selectionSort();
                
        long endTime = System.nanoTime();

        System.out.println("Selection Sort execution time: " + (endTime - startTime) + " nanoseconds.");
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

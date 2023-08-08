import java.util.List;
import java.util.ArrayList;
import java.util.Map;

public class MergeSort {
	myMap originalMap;
	myMap sortedMap;
	List<String> aux;

	/**
	 * Constructs a MergeSort object with the given original map.
	 *
	 * @param originalMap the original map containing the data to be sorted
	 */
	public MergeSort(myMap originalMap) {
		this.originalMap = originalMap;
		this.aux = new ArrayList<String>(this.originalMap.map.keySet());
		this.sortedMap = new myMap();
	}
	/**
	 * Merges two subarrays of the array during the Merge Sort algorithm.
	 *
	 * @param l starting index of the left subarray
	 * @param m the middle index of the array
	 * @param r ending index of the right subarray
	 */
	public void merge(int l, int m, int r)
	{
		int n1 = m - l + 1;
	    int n2 = r - m;

	    int L[] = new int[n1];
	    String Left[] = new String[n1];
	    int R[] = new int[n2];
	    String Right[] = new String[n2];

	    for (int i = 0; i < n1; ++i) 
		{
	       L[i] = originalMap.map.get(((List<String>) this.aux).get(l + i)).count;
	       Left[i] = this.aux.get(l + i);
	    }
	    for (int j = 0; j < n2; ++j) 
		{
	    	R[j] = originalMap.map.get(((List<String>) this.aux).get(m + 1 + j)).count;
	    	Right[j] = this.aux.get(m + 1 + j);
	    }

	 
	    int i = 0, j = 0;
	    int k = l;
	    while (i < n1 && j < n2) 
		{
	    	if (L[i] <= R[j]) 
			{
	    		aux.set(k, Left[i]);
	    		i++; 	    		
	        }
	    	
	        else 
			{
	    		aux.set(k, Right[j]);
	        	j++;
	        }
	    	
	    	k++;
	    }
	 
	    while (i < n1) 
		{
    		aux.set(k, Left[i]);
	    	i++;
	    	k++;
	    }
	 
	    while (j < n2)
		{
    		aux.set(k, Right[j]);
	    	j++;
	        k++;
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
	 * Helper method for performing the recursive sorting process.
	 *
	 * @param l starting index of the subarray
	 * @param r ending index of the subarray
	 */
	private void sortHelper (int l, int r) 
	{
		if (l < r) 
		{
	        int m = l + (r - l) / 2;
	        sortHelper(l, m);
	        sortHelper(m + 1, r);
	        merge(l, m, r);
		}
	    
	}
	/**
     * Sorts the original map using the merge sort algorithm.
     */
	public void sort(){		
		
		long startTime = System.nanoTime();

		
	    sortHelper (0, this.originalMap.mapSize - 1);
		long endTime = System.nanoTime();

        System.out.println("Merge Sort execution time: " + (endTime - startTime) + " nanoseconds.");
	    generateNewMap();
	}
	/**
     * Prints the sorted map
     */
	public void printSortedArray(){
	    for (Map.Entry<String, info> e : sortedMap.map.entrySet())
		{
            System.out.println("Letter: " + e.getKey() + " - Count: "+ e.getValue().count + " - Words: " + e.getValue().words);
		}
                               
	}
    /**
     * Prints the sorted map
     */
	public void printOriginalArray(){
	    for (Map.Entry<String, info> e : originalMap.map.entrySet())
		{
			System.out.println("Letter: " + e.getKey() + " - Count: "+ e.getValue().count + " - Words: " + e.getValue().words);
		}
            
                               
	}
}
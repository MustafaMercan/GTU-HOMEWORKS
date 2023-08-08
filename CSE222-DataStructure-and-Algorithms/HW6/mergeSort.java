import java.util.Map;
import java.util.ArrayList;

public class mergeSort{

    myMap original_map;
    myMap sorted_map;

/**
 * This constructor method sorts the given object of type 'myMap' by performing merge sort.
 * @param input The variable of type 'myMap' holds the data that we want to sort.
 */
    public mergeSort(myMap input)
    {
        if(input.str != null)
        {
            this.original_map = input;
            this.sorted_map = this.merge_sort_helper(original_map);
            System.out.println("The Sorted map: ");
            sorted_map.print_map();
        }
        else
        {
            System.out.println("Invalid input. Input is empty");
            return;
        }

    }
/**
 * This method utilizes the merge sort algorithm to perform the sorting operation.
 * @param input This parameter takes the portion to be sorted.
 */
public myMap merge_sort_helper(myMap input) 
{
    if (input.get_size() <= 1)
        return input;

    myMap leftMap = new myMap();
    myMap rightMap = new myMap();

    int middle = input.get_size() / 2;
    int i = 0;

    ArrayList<Character> keys = new ArrayList<>(input.get_hash_map().keySet());

    for (int j = 0; j < keys.size(); j++) 
    {
        Character key = keys.get(j);
        info value = input.get_hash_map().get(key);

        if (i < middle) 
        {
            leftMap.add_element(key, value);
        } 
        else 
        {
            rightMap.add_element(key, value);
        }
        i++;
    }

    leftMap = merge_sort_helper(leftMap);
    rightMap = merge_sort_helper(rightMap);

    return merge_map(leftMap, rightMap);
}
/**
 * This method allows the merging of two different maps by sorting them
 * @param leftMap It holds the myMap data that needs to be merged.
 * @param rightMap It holds the myMap data that needs to be merged.
 */
public myMap merge_map(myMap leftMap, myMap rightMap) 
{
    myMap mergeMap = new myMap();

    while (leftMap.get_size() != 0 && rightMap.get_size() != 0) 
    {
        Character leftKey = null;
        info leftInfo = null;
        for (Character key : leftMap.get_hash_map().keySet()) 
        {
            leftKey = key;
            leftInfo = leftMap.get_hash_map().get(key);
            break;
        }

        Character rightKey = null;
        info rightInfo = null;
        for (Character key : rightMap.get_hash_map().keySet()) 
        {
            rightKey = key;
            rightInfo = rightMap.get_hash_map().get(key);
            break;
        }

        if (leftInfo.get_count() <= rightInfo.get_count()) 
        {
            mergeMap.add_element(leftKey, leftInfo);
            leftMap.remove_element(leftKey);
        } 
        else 
        {
            mergeMap.add_element(rightKey, rightInfo);
            rightMap.remove_element(rightKey);
        }
    }

    mergeMap.put_all(leftMap);
    mergeMap.put_all(rightMap);

    return mergeMap;
}

}
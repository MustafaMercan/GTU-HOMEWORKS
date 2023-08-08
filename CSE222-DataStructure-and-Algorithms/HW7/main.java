

public class main {

	public static void main(String[] args) { 
		// String str = "'Hush, hush!' whispered the rushing wind.";
        
        String str = "a bb ccc dddd eeee";
        //String str = "a bb ccc d eee ff g";
		//String str = "a ab abc abcd abcde";
		


       
		// MERGE SORT \\
		myMap newMapObj = new myMap();
		newMapObj.buildMap(str);
        
		System.out.println("Original String:\t" + str);
		System.out.println("Preprocessed String:\t" + newMapObj.str);
		MergeSort ms = new MergeSort(newMapObj);

		System.out.println("\n\nThe original (unsorted) map:");
		ms.printOriginalArray();

		System.out.println("\n\nThe sorted map:");
		ms.sort();
		ms.printSortedArray();


		// SELECTION SORT \\

		myMap newMapObj2 = new myMap();
        newMapObj2.buildMap(str);
        System.out.println("Original String:\t" + str);
        System.out.println("Preprocessed String:\t" + newMapObj2.str);

        SelectionSort ss = new SelectionSort(newMapObj2);

        System.out.println("\n\nThe original (unsorted) map:");
        ss.printOriginalArray();

        System.out.println("\n\nThe sorted map:");
        ss.sort();
        ss.printSortedArray();




		// INSERTION SORT \\
		myMap newMapObj3 = new myMap();
        newMapObj3.buildMap(str);
        System.out.println("Original String:\t" + str);
        System.out.println("Preprocessed String:\t" + newMapObj3.str);

        InsertionSort is = new InsertionSort(newMapObj3);

        System.out.println("\n\nThe original (unsorted) map:");
        is.printOriginalArray();

        System.out.println("\n\nThe sorted map:");
        is.sort();
        is.printSortedArray();

		// BUBBLE SORT \\


		myMap newMapObj4 = new myMap();
        newMapObj4.buildMap(str);
        System.out.println("Original String:\t" + str);
        System.out.println("Preprocessed String:\t" + newMapObj4.str);

        BubbleSort bs = new BubbleSort(newMapObj4);

        System.out.println("\n\nThe original (unsorted) map:");
        bs.printOriginalArray();

        System.out.println("\n\nThe sorted map:");
        bs.sort();
        bs.printSortedArray();

		//QUICK SORT \\

        myMap newMapObj5 = new myMap();
        newMapObj5.buildMap(str);
        System.out.println("Original String:\t" + str);
        System.out.println("Preprocessed String:\t" + newMapObj5.str);

        QuickSort qs = new QuickSort(newMapObj5);

        System.out.println("\n\nThe original (unsorted) map:");
        qs.printOriginalArray();

        System.out.println("\n\nThe sorted map:");
        qs.sort();
        qs.printSortedArray();
		
	}
}
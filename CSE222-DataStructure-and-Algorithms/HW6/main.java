public class main
{
    public static void main(String [] args)
    {

        System.out.println("\n\n ===== TEST 1 =====\n");

        myMap map_test1 = new myMap("Buzzing bees buzz.");
        mergeSort sort_test1 = new mergeSort(map_test1);

        System.out.println("\n\n=======================\n");

        
        
        System.out.println("\n\n ===== TEST 2 =====\n");

        myMap map_test2 = new myMap("this is a test cases.");
        mergeSort sort_test2 = new mergeSort(map_test2);

        System.out.println("\n\n=======================\n");





        System.out.println("\n\n ===== Error Cases 1 =====\n");

        myMap map_test3 = new myMap("");
        mergeSort sort_test3 = new mergeSort(map_test3);

        System.out.println("\n\n=======================\n");


        System.out.println("\n\n ===== Error Cases 2 =====\n");

        myMap map_test4 = new myMap("    ");
        mergeSort sort_test4  = new mergeSort(map_test4);

        System.out.println("\n\n=======================\n");


        System.out.println("\n\n ===== Error Cases 3 =====\n");

        myMap map_test5 = new myMap("   £$£$>#£124!2512  ");
        mergeSort sort_test5 = new mergeSort(map_test5);

        System.out.println("\n\n=======================\n");





        

    }
}
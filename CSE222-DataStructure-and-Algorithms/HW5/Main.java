import java.util.Scanner;

public class Main{

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        String input;

      MyTree myTree = new MyTree();//part A


       System.out.println("--------------- PART B ---------------");

       System.out.println("Please enter a input for part B(BFS SEARCH)");
        System.out.print("Input : ");
        input = scanner.nextLine();
        myTree.bfs_search(input);



       System.out.println("--------------- PART C ---------------");

       System.out.println("Please enter a input for part C(DFS SEARCH)");
        System.out.print("Input : ");
       input = scanner.nextLine();
       myTree.dfs_search(input);



        System.out.println("--------------- PART D ---------------");
        System.out.println("Please enter a input for part D(Post Order Traversal)");
        System.out.print("Input : ");
        input = scanner.nextLine();
        myTree.post_order_traversal(input);




        System.out.println("--------------- PART E ---------------");
        System.out.println("Please enter a input for part E(Move Node)");

        System.out.print("Input for search (format example : example1->example2->example3->example4):");
        input = scanner.nextLine();

        System.out.print("Input for destination year (format example : 5555):");
        String dest = scanner.nextLine();

        
        myTree.move_node(input,dest);
    }
}
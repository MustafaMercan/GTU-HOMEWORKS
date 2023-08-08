import java.util.*;

public class Node{

    public int x; // it holds x value
    public int y;// it holds y value

    public Node(int y, int x)
    {
        this.y = y;
        this.x = x;
    }
    public void print()// it prints y and x value
    {
        System.out.println("y -> " +this.y + " x -> "+this.x);
    }
}
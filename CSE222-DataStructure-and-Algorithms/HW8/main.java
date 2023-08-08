import java.util.*;

public class main{
    public static void main(String [] args)
    {


        new Thread (new TestCases("./Maps(inputs)/map01.txt",500,500)).start();
        new Thread (new TestCases("./Maps(inputs)/map02.txt",500,500)).start();
        
        new Thread (new TestCases("./Maps(inputs)/map03.txt",500,500)).start();
        new Thread (new TestCases("./Maps(inputs)/map04.txt",500,500)).start();

        new Thread (new TestCases("./Maps(inputs)/map05.txt",500,500)).start();
        new Thread (new TestCases("./Maps(inputs)/map06.txt",500,500)).start();
        new Thread (new TestCases("./Maps(inputs)/map07.txt",500,500)).start();
        new Thread (new TestCases("./Maps(inputs)/map08.txt",500,500)).start();
        new Thread (new TestCases("./Maps(inputs)/map09.txt",500,500)).start();
        new Thread (new TestCases("./Maps(inputs)/map10.txt",500,500)).start();
        

        new Thread (new TestCases("./Maps(inputs)/tokyo.txt",1000,1000)).start();
        new Thread (new TestCases("./Maps(inputs)/pisa.txt",1000,1000)).start();
        new Thread (new TestCases("./Maps(inputs)/triumph.txt",1000,1000)).start();
        new Thread (new TestCases("./Maps(inputs)/vatican.txt",1000,1000)).start();



    }
}
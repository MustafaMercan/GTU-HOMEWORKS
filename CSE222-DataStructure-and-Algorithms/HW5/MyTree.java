import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;


import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;
import java.util.ArrayList;

public class MyTree extends JFrame {


    DefaultMutableTreeNode rootNode;
    JTree courseTree;
    DefaultTreeModel treeModel;
    int counter;


//===============================PART A ================================\\


/**
 *This method is the constructor method. Within this method, files are read from the txt file, parsed, and a tree is created.
 *  
 */
    
    public MyTree() 
    {
        setTitle("Output");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.counter = 1;

        ArrayList<String[]> arrList = new ArrayList<String[]>();

        this.rootNode = new DefaultMutableTreeNode("root");
        this.treeModel = new DefaultTreeModel(this.rootNode);
        this.courseTree = new JTree(this.treeModel);

        try
        {

            BufferedReader reader = new BufferedReader(new FileReader("tree.txt"));

            String line = reader.readLine();
            while(line != null)
            {
                String[] str = line.split(";");
                arrList.add(str);
                line = reader.readLine();
            }
            reader.close();

            for(int i = 0 ; i < arrList.size() ; i++)
            {
                DefaultMutableTreeNode parentNode = this.rootNode;
                for(int j = 0 ; j < arrList.get(i).length ; j++)
                {
                    String part = arrList.get(i)[j];
                    DefaultMutableTreeNode node = findNodeChild(parentNode,part);
                    if(node == null)
                    {
                        node = new DefaultMutableTreeNode(part);
                        parentNode.add(node);
                    }
                    parentNode = node;
                }
            }
        }
        catch(Exception err)
        {
            err.printStackTrace();

        }
        JScrollPane scrollPane = new JScrollPane(courseTree);
        getContentPane().add(scrollPane);
        setSize(450, 650);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    /**
     * This method updates the tree and prints it to the screen whenever a change is made in the tree.
     */
    public void update_tree() 
    {
        DefaultTreeModel newModel = new DefaultTreeModel(this.rootNode);
        courseTree.setModel(newModel);

        JScrollPane scrollPane = new JScrollPane(courseTree);
        getContentPane().removeAll();
        getContentPane().add(scrollPane);
        setSize(450, 650);
        setLocationRelativeTo(null);
        setVisible(true);
}

    
//===============================PART B ================================\\

/**
 * This method checks if the input provided by the user exists in our tree by using the BFS algorithm.
 * @param input holds the data that the user wants to search for.
 */
    public void bfs_search(String input) 
    {
        Queue<DefaultMutableTreeNode> nodeQueue = new LinkedList<>();

        nodeQueue.add(rootNode);
        int step = 1;
        
        while (!nodeQueue.isEmpty()) 
        {
            DefaultMutableTreeNode currentNode = nodeQueue.poll();
            
            if (currentNode.getUserObject().toString().equals(input)) 
            {
                System.out.println("step" + step + " -> " + currentNode.getUserObject().toString() + "(FOUND!)");
                return;
            } 
            else 
            {
                System.out.println("step" + step + " -> " + currentNode.getUserObject().toString());
                for (int i = 0; i < currentNode.getChildCount(); i++) 
                {
                    DefaultMutableTreeNode childNode = (DefaultMutableTreeNode) currentNode.getChildAt(i);
                    nodeQueue.add(childNode);
                }
                step++;
            }
        }
        System.out.println("Input not found!");
    }

//===============================PART C ================================\\

/**
 * This method checks if the input provided by the user exists in our tree by using the DFS algorithm.
 * @param input holds the data that the user wants to search for.
 */
public void dfs_search(String input) {

    Stack<DefaultMutableTreeNode> nodeStack = new Stack<>();
    nodeStack.push(this.rootNode);
    int step = 1;
    while (!nodeStack.isEmpty()) 
    {
        DefaultMutableTreeNode currentNode = nodeStack.pop();
        if (currentNode.getUserObject().toString().equals(input)) 
        {
            System.out.println("step" + step + " -> " + currentNode.getUserObject().toString() + "(FOUND!)");
            return;
        } 
        else 
        {
            System.out.println("step" + step + " -> " + currentNode.getUserObject().toString());
            for (int i = 0  ; i < currentNode.getChildCount() ; i++) 
            {
                DefaultMutableTreeNode childNode = (DefaultMutableTreeNode) currentNode.getChildAt(i);
                nodeStack.push(childNode);
            }
            step++;
        }
    }
    System.out.println("Input not found!");
}
//===============================PART D ================================\\


/**
 * This method checks if the input provided by the user exists in our tree by using the Post Order Traversal algorithm.
 * @param input holds the data that the user wants to search for.
 */
public void post_order_traversal(String input) 
{
    this.counter = 1;
    if(!this.post_order_traversal(this.rootNode,input))
        System.out.println("Not Found");
}
/**
 * This method checks if the input provided by the user exists in our tree by using the Post Order Traversal algorithm.
 * @param input holds the data that the user wants to search for.
 * @param node holds the current node.
 */
public boolean post_order_traversal(DefaultMutableTreeNode node,String input) {
    if (node == null) 
    {
        return false;
    }
    int childCount = node.getChildCount();
    for (int i = 0; i < childCount; i++) 
    {
        DefaultMutableTreeNode child = (DefaultMutableTreeNode) node.getChildAt(i);
        if(post_order_traversal(child,input))
            return true;
    }
    if(node.getUserObject().equals(input))
    {
        System.out.println("Step " + this.counter + "-> " + node.getUserObject() + " (Founded!!)");
        return true;
    }
    else
    {
        if(!node.getUserObject().equals("root"))
        {
            System.out.println("Step " + this.counter + " -> "+ node.getUserObject());
            this.counter = this.counter + 1;
        }
        return false;
    }
}
/**
 * This method checks the children of the parent node and returns the value if it is found, otherwise returns null.
 * @param parentNode holds parent node
 * @param name holds node's name with string
 */
private DefaultMutableTreeNode findNodeChild(DefaultMutableTreeNode parentNode, String name)
{
    if(parentNode == null)
    {
        return null;
    }
    for(int i = 0 ; i < parentNode.getChildCount(); i++)
    {
        DefaultMutableTreeNode child = (DefaultMutableTreeNode) parentNode.getChildAt(i);
        if(child.getUserObject().equals(name))
            return child;
    }
    return null;

}

//===============================PART E ================================\\
/**
 * This method allows us to move a node from its current position to another position in tree.
 * @param src  holds the path of the node we want to move.
 * @param dest holds the year we want to move the node to.
 */
public void move_node(String src, String dest)
{
    Queue<String> queue = new LinkedList<>();
    Queue <DefaultMutableTreeNode> nodeQueue = new LinkedList <>();
    DefaultMutableTreeNode moveNode = null;

    
    String[] parts = src.split("->");
    for (String part : parts) 
        queue.add(part);

    DefaultMutableTreeNode destNode = findNodeChild(this.rootNode,dest);
    if(destNode == null)
    {
        destNode = new DefaultMutableTreeNode(dest);
        this.rootNode.add(destNode);
    }
    DefaultMutableTreeNode parentNode = this.rootNode;
    while (!queue.isEmpty())
    {
        String part = queue.remove();
        moveNode = findNodeChild(parentNode,part);
        if(moveNode != null)
        {
            nodeQueue.add(moveNode);
            parentNode = moveNode;
        }
        else
        {
            System.out.println("Node not found!!");
            this.clear_node();
            return;
        }
    }

    moveNode.removeFromParent();
    if(nodeQueue.size() > 0)
        nodeQueue.remove();
    parentNode = destNode;
    while(nodeQueue.size() != 0)
    {
        String node = nodeQueue.remove().getUserObject().toString();
        DefaultMutableTreeNode tmpNode = findNodeChild(parentNode,node);
        if(tmpNode == null)
        {
            if(nodeQueue.size() == 0)
            {
                parentNode.add(moveNode);
            }
            else
            {
                tmpNode = new DefaultMutableTreeNode(node);
                parentNode.add(tmpNode);
            }
        }
        else if(nodeQueue.size() == 0)
        {
            System.out.println(moveNode.getUserObject().toString() + " has been overwritten");
            tmpNode.removeFromParent();
            parentNode.add(moveNode);
        }
        parentNode = tmpNode;
    }
    clear_node();  
    update_tree();
    System.out.println("Moved " + src + " to " + dest);

}

/**
 * This method deletes a node from the tree if it doesn't have any child nodes, whether it is a course or year.
 */
private void clear_node()
{
    DefaultMutableTreeNode currNode = this.rootNode;
    Queue<DefaultMutableTreeNode> nodeQueue = new LinkedList<>();
    if(this.rootNode == null)
        return;
    
    nodeQueue.add(this.rootNode);
    while(!nodeQueue.isEmpty())
    {
        DefaultMutableTreeNode currentNode = nodeQueue.poll();
        if(currentNode.getChildCount() == 0 && (currentNode.getUserObject().toString().matches("\\d+") || currentNode.getUserObject().toString().contains("CSE")))
        {
            currentNode.removeFromParent();
            this.clear_node();
        }
        for(int i = 0 ; i <currentNode.getChildCount()  ; i++)
        {
            DefaultMutableTreeNode childNode = (DefaultMutableTreeNode) currentNode.getChildAt(i);
            nodeQueue.add(childNode);
        }
    }
}
}


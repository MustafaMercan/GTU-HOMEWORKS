import java.util.*;
public class CSE222Graph{


    //holds Node as the key and stores a list of edge nodes belonging to the key node as the value
    public Map<Node, List<Node>> node_list_with_edge; 

    //holds data in the format of "y-x" as the key, and holds the node located at that coordinate as the value
    public Map<String,Node> nodes;

    public Node start_node; //holds the start node
    public Node end_node; // golds the target node
    public int count; // holds the number of created nodes


    public CSE222Graph(CSE222Map map)
    {
        
        this.node_list_with_edge = new HashMap<>();
        this.nodes = new HashMap<>();
        this.count = 0;
        create_graph(map);

        this.start_node = get_node(map.start_points[0],map.start_points[1]);
        this.end_node = get_node(map.end_points[0],map.end_points[1]);

        System.out.println("===============Graph was created===========");
        
        System.out.println("start cord. -> " + start_node.y + " " + start_node.x);
        System.out.println("end cord. -> " + end_node.y + " " + end_node.x);

        System.out.println("===========================================");

    }

    public void add_node(Node new_node)
    {
        this.node_list_with_edge.put(new_node,new ArrayList<>());
        this.nodes.put(new_node.y+"-"+new_node.x,new_node);
    }

    public void add_edge(Node src, Node dest)
    {
        node_list_with_edge.get(src).add(dest);
    }

    public Node get_node(int y, int x)
    {
        String key = y + "-" + x;
        Node current_node = this.nodes.get(key);

        return current_node;
    }

    public void create_graph(CSE222Map input)
    {


        for(int i = 0; i < input.map.length;i++)
        {
            for(int j = 0 ; j < input.map[i].length ; j++)
            {
                if(input.map[i][j] == 0)
                {
                    Node newNode = new Node(i,j);
                    add_node(newNode);
                    this.count++;

                }
            }
        }
        
        for(int i = 0 ; i < input.map.length; i++)
        {
            for(int j = 0 ; j < input.map[i].length ; j++)
            {
                if(input.map[i][j] == 0)
                {
                    Node src = get_node(i,j);
                    if(src == null)
                    {
                        System.out.println("Error 1");
                        return ;
                    }

                    if(i-1 >= 0)
                    {
                        if(input.map[i-1][j] == 0)
                        {
                            Node edge = get_node(i-1,j);
                            add_edge(src,edge);
                        }
                    }

                    if(i+1 < input.map.length)
                    {
                        if(input.map[i+1][j] == 0)
                        {
                            Node edge = get_node(i+1,j);
                            add_edge(src,edge);
                        }
                    }

                    if(j-1 >= 0)
                    {
                        if(input.map[i][j-1] == 0)
                        {
                            Node edge = get_node (i,j-1);
                            add_edge(src,edge);
                        }
                    }

                    if(j + 1 < input.map[i].length)
                    {
                        if(input.map[i][j+1] == 0)
                        {
                            Node edge = get_node(i,j+1);
                            add_edge(src,edge);
                        }
                    }

                    if(i - 1 >= 0 && j-1 >= 0)
                    {
                        if(input.map[i-1][j-1] == 0)
                        {
                            Node edge = get_node(i-1,j-1);
                            add_edge(src,edge);
                        }
                    }

                    if(i - 1 >= 0 && j + 1 < input.map[i].length)
                    {
                        if(input.map[i-1][j+1] == 0)
                        {
                            Node edge = get_node(i-1,j+1);
                            add_edge(src,edge);
                        }
                    }

                    if(i + 1 < input.map.length && j + 1 < input.map[i].length)
                    {
                        if(input.map[i+1][j+1] == 0)
                        {
                            Node edge = get_node(i+1,j+1);
                            add_edge(src,edge);
                        }
                    }

                    if(i + 1 < input.map.length && j - 1 >= 0)
                    {
                        if(input.map[i+1][j-1] == 0)
                        {
                            Node edge = get_node(i+1,j-1);
                            add_edge(src,edge);
                        }
                    }
                }
            }
        }
    }
    public void print_graph()
    {
        for (Map.Entry<Node, List<Node>> entry : node_list_with_edge.entrySet()) 
        {
            Node key = entry.getKey();
            List<Node> value = entry.getValue();
            System.out.println("Key: " + key + ", Value: " + value);
        }

    }
}
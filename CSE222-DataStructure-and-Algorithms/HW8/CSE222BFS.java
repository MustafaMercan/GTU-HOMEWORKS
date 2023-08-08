import java.util.*;

public class CSE222BFS{

    CSE222Graph graph;// it holds the graph of type CSE222Graph
    Node start_node;// it holds the start node of type Node
    Node end_node; // it holds the target node of type Node

    public CSE222BFS(CSE222Graph input)
    {
        this.graph = input;
        this.start_node = input.start_node;
        this.end_node = input.end_node;
    }

    public List<Node> findPath()
    {
        long start_time = System.nanoTime();

        
        Map<Node, Node> previous = new HashMap<>();
        Queue<Node> queue = new LinkedList<>();
        Set<Node> visited = new HashSet<>();

        queue.offer(start_node);
        visited.add(start_node);

        while (!queue.isEmpty()) 
        {
            Node current_node = queue.poll();

            if (current_node == end_node)
                break;

            List<Node> neighbors = graph.node_list_with_edge.get(current_node);

            for (Node neighbor : neighbors) 
            {
                if (!visited.contains(neighbor)) {
                    queue.offer(neighbor);
                    visited.add(neighbor);
                    previous.put(neighbor, current_node);
                }
            }
        }

        List<Node> shortest_path = new ArrayList<>();
        Node current_node = end_node;

        while (current_node != null) 
        {
            shortest_path.add(0, current_node);
            current_node = previous.get(current_node);
        }

        long end_time = System.nanoTime();
        long duration = end_time - start_time;
        double milliseconds = duration / 1_000_000.0;
        System.out.println("Runtime BFS: " + milliseconds + " ms");
        System.out.println("====================================");

        return shortest_path;
    }



}
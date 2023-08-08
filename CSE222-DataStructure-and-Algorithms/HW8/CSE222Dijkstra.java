import java.util.*;
public class CSE222Dijkstra{
    
    CSE222Graph graph;
    Node start_node;
    Node end_node;

    public CSE222Dijkstra(CSE222Graph input)
    {
        this.graph = input; // it holds the graph of type CSE222Graph
        this.start_node = input.start_node;// it holds the start node of type Node
        this.end_node = input.end_node; // it holds the target node of type Node
    }
    
    public List<Node> findPath() 
    {
        long start_time = System.nanoTime();

        Map<Node, Integer> distances = new HashMap<>();
        Map<Node, Node> previous = new HashMap<>();
        Set<Node> visited = new HashSet<>();

        PriorityQueue<Node> priorityQueue = new PriorityQueue<>(Comparator.comparingInt(distances::get));

        for (Node node : graph.node_list_with_edge.keySet()) 
        {
            if (node == start_node) {
                distances.put(node, 0);
            } 
            else 
            {
                distances.put(node, Integer.MAX_VALUE);
            }
            priorityQueue.offer(node);
        }

        while (!visited.contains(end_node)) 
        {
            Node current_node = priorityQueue.poll();
            visited.add(current_node);

            List<Node> neighbors = graph.node_list_with_edge.get(current_node);

            for (Node neighbor : neighbors) 
            {
                int distance = distances.get(current_node) + 1;
                if (distance < distances.get(neighbor)) 
                {
                    distances.put(neighbor, distance);
                    previous.put(neighbor, current_node);
                    priorityQueue.remove(neighbor);
                    priorityQueue.offer(neighbor);
                }
            }
        }

        List<Node> shortest_path = new ArrayList<>();
        Node current_node = end_node;

        while (current_node != null) {
            shortest_path.add(0, current_node);
            current_node = previous.get(current_node);
        }

        long end_time = System.nanoTime();
        long duration = end_time - start_time;
        double milliseconds = duration / 1_000_000.0;
        System.out.println("====================================");

        System.out.println("Runtime Dijkstra: " + milliseconds + " ms");

        return shortest_path;
    }
}
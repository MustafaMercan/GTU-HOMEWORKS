import java.util.*;
public class TestCases implements Runnable{

    public String map_path;
    public int y;
    public int x;

    public TestCases(String map_path, int y, int x)
    {
        this.map_path = map_path;
        this.y = y;
        this.x = x;
    }
    public void run()
    {
        CSE222Map map = new CSE222Map(map_path,y,x); // +

        String[] parts = map_path.split("/");

        
        String fileNameWithExtension = parts[parts.length - 1];
        
        String fileName = fileNameWithExtension.replace(".txt", "");
        
        
        String map_png_path = "./Maps(outputs)/"+fileName+".png";
        
        map.map_to_png(map_png_path);


        CSE222Graph graph = new CSE222Graph(map);

        CSE222Dijkstra dijkstra = new CSE222Dijkstra(graph);

        List <Node> dijkstraPath = dijkstra.findPath();

        CSE222BFS bfs = new CSE222BFS(graph);

        List <Node> bfsPath = bfs.findPath();

        map.draw_line(dijkstraPath);
        map.draw_line(bfsPath);

        System.out.println("====================================");

        System.out.println("Dijkstra path size = " + dijkstraPath.size());
        System.out.println("BFS path size = " + bfsPath.size());
        System.out.println("====================================");

        map.write_path(dijkstraPath);

        map.write_path(bfsPath);


    }
}
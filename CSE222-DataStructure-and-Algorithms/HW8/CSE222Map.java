import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.awt.image.BufferedImage;
import java.io.IOException;
import javax.imageio.ImageIO;
import java.awt.Color;
import java.awt.Graphics2D;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.*;


public class CSE222Map{

    String path_name;// it holds input path name
    String file_name;// it holds input file name

    public int [][] map; // it holds NxN matrix
    public int [] start_points; // it holds y-x values
    public int [] end_points; // it holds y-x values
    //The parameters flag1 and flag2 are used in the draw_line method to respectively draw the paths of the Dijkstra and BFS algorithms.
    boolean flag1;
    boolean flag2;

    public CSE222Map(String input,int y, int x)
    {
        this.flag1 = true;
        this.flag2 = true;


        this.path_name = input;

        String [] parts = path_name.split("/");
        this.file_name = parts[parts.length - 1].replace(".txt","");

        this.map = new int [y][x];
        this.start_points = new int[2];
        this.end_points = new int[2];

        this.read_input(input);

    }
    private void read_input(String file_name)
    {
        File file = new File(file_name);
        try{

            Scanner scanner = new Scanner(file);
            
            String start_point = scanner.nextLine();
            String[] tmp_cord = start_point.split(",");

            this.start_points[0] = Integer.parseInt(tmp_cord[0].trim());
            this.start_points[1] = Integer.parseInt(tmp_cord[1].trim());

            String end_point = scanner.nextLine();
            String [] tmp2_cord = end_point.split(",");

            this.end_points[0] = Integer.parseInt(tmp2_cord[0].trim());
            this.end_points[1] = Integer.parseInt(tmp2_cord[1].trim());

            int row_index = 0;
            while(scanner.hasNextLine())
            {
                String line = scanner.nextLine();
                String[] points = line.split(",");
                for(int column_index = 0 ; column_index < points.length ; column_index++)
                {
                    map[row_index][column_index] = Integer.parseInt(points[column_index].trim());
                }

                row_index++;
            }
            scanner.close();

            for(int i = 0 ; i < map.length ; i++)
            {
                for(int j = 0 ; j < map[i].length ; j++)
                {
                    if(map[i][j] == -1)
                    {
                        map[i][j] = 1;
                    }
                }
            }
        }
        catch(FileNotFoundException e)
        {
            e.printStackTrace();
        }
    }
    public void map_to_png(String path)
    {
         BufferedImage image = new BufferedImage(map.length, map[0].length, BufferedImage.TYPE_INT_ARGB);

        for(int i = 0 ; i < map.length ; i++)
        {
            for(int j = 0 ; j < map[i].length ; j++)
            {
                int color = (map[i][j] == 1) ? 0xFF000000 : 0xFFFFFFFF;
                image.setRGB(i, j, color);
            }
        }
        try 
        {
            File output = new File(path);
            ImageIO.write(image, "png", output);
            System.out.println("PNG was created: " + output.getAbsolutePath());
        } 
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }


    
    public void draw_line(List <Node> path)
    {
        try{
            String map_path = "./Maps(outputs)/"+this.file_name+".png";
            BufferedImage image = ImageIO.read(new File(map_path));
            File imageFile = new File(map_path);


            for(Node node : path)
            {
                int y = node.y;
                int x = node.x;
                image.setRGB(y,x,0xFFFF0000);
            }
            String new_map_path;
            if(flag1)
                new_map_path = "./Maps(outputs)/"+this.file_name+"_dijkstra.png";
            else
                new_map_path = "./Maps(outputs)/"+this.file_name+"_BFS.png";
            File output = new File(new_map_path);
            ImageIO.write(image, "png", output);
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }

        if(flag1 == true)
            flag1 = false;
        else
            flag1 = true;

    }
    public void write_path(List <Node> path)
    {
        try
        {   
            String output_path ;

            if(flag2)
                output_path = "./Text(path)/"+file_name.replace(".txt","")+"_dijkstra_path.txt";
            else
                output_path = "./Text(path)/"+file_name.replace(".txt","")+"_bfs_path.txt";
            BufferedWriter writer = new BufferedWriter(new FileWriter(output_path));
            for(Node node : path)
            {
                int y = node.y;
                int x = node.x;
                writer.write(String.valueOf(y) +"," + String.valueOf(x));
                writer.newLine();
            }
            writer.close();

        }
        catch(IOException e)
        {
            e.printStackTrace();
        }

        if(flag2 == true)
            flag2 = false;
        else
            flag2 = true;
    }
}
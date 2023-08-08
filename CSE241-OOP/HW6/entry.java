import java.util.ArrayList;
import java.util.List;
public class entry extends Observable {
    
    //public List<viewer> viewer_list;
    //public List<player> player_list;

    //public List<entry> type_list;
    public String type;//holds type
    public String get_name() { return "1";}
    public String get_other_information() { return "1";}
    public String get_dimension_information(){ return "1";}
    public String get_duration() { return"1";}
    public void add(audio a1)
    {
        notification(a1);
    }
    public void add(video v1)
    {
        notification(v1);
    }
    public void add(image i1)
    {
        notification(i1);
    }
    public void add(text t1)
    {
        notification(t1);
    }
    public void remove(playable p1)
    {
        notification_element(p1);
    }
    public void remove(non_playable np)
    {
        notification_element(np);
    }
    entry(){
        //type_list = new ArrayList<>();
        //viewer_list = new ArrayList<>();
        //player_list = new ArrayList<>();
        //System.out.print("Created entry class\n");
    }
    public void deneme()
    {
        //notification();
    }
    
}

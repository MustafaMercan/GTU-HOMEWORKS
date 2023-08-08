import java.util.ArrayList;
import java.util.List;
public class player implements Observer{
    public List<entry> list;//holds elements
    public int current_index;//holds index
    public int size;//holds size of element
    public void update_2(image i1){ }//this function for viewer class
    public void update_2(text t1){ }//this function for viewer class
    player(){
        list = new ArrayList<>();
        current_index = 0;
        size = 0;
    }
    public entry currently_playing()
    {
        if(size == 0)
        {
            System.out.print("Empty list\n");
            return null;
        }
        else
            return list.get(current_index);
    }
    @Override
    public void update(audio a1){
        entry tmp = (entry) a1;
        list.add(tmp);
        size++;
    }
    public void previous(String type)
    {
        if(size == 0)
        {
            System.out.print("the play list is empty\n");
        }
        else
        {
            current_index--;
            playable p1;
            if(current_index < 0)
            {
                System.out.print("invalid value.current index was reseted\n");
                current_index = 0;   
            }
            else
            {
                for(;current_index>-1;current_index--)
                {
                    p1 = (playable) this.currently_playing();
                    if(p1.get_type() == type)
                    {
                        break;
                    }
                }
                p1 = (playable) this.currently_playing();
                if(p1.get_type() != type)
                {
                    System.out.print("next "+ type+ " couldn't found so current index was reseted\n");
                    current_index = 0;
                }
            }
        }

    }
    public void next(String type)
    {
        if(size == 0)
        {
            System.out.print("the play list is empty\n");
        }
        else
        {
            current_index++;
            playable p1;
            if(current_index == size)
            {
                System.out.print("invalid value.current index was reseted\n");
                current_index = 0;
            }
            else
            {
                for(;current_index<size-1 ; current_index++)
                {
                    p1 = (playable) this.currently_playing();
                    if(p1.get_type() == type)
                    {
                        break;
                    }
                }
                p1 = (playable) this.currently_playing();
                if(p1.get_type() != type)
                {
                    System.out.print("next "+ type+ " couldn't found so current index was reseted\n");
                    current_index = 0;
                }
            }         
        }

    }
    public void update(video v1)
    {

        entry tmp = (entry) v1;
        size++;
        list.add(tmp);
        
    }
    public void update_remove_element(playable p1)
    {
        entry e1 = (entry) p1;
        size--;
        list.remove(e1);
    }
    public void show_list()
    {
        for(entry tmp : list)
        {
            System.out.print(tmp.get_name() +" "+tmp.get_duration()+ " " + tmp.get_other_information() +"\n");
        }
    }
    public void update_remove_element(non_playable np1){ }
}

import java.util.ArrayList;
import java.util.List;
public class viewer implements Observer {
    
    public List<entry> list;//holds elements
    public int current_index;//holds index
    public int size;//holds size
    public void update(audio a1){ }//this function for player class
    public void update(video v1){ }//this function for player class
    public void update_remove_element(playable np1){ }

    viewer()
    {
        list = new ArrayList<>();
        current_index = 0;
        size = 0;
    }
    public void update_2(image i1)
    {
        entry tmp = (entry) i1;
        size++;
        list.add(tmp);
    }
    public void update_2(text t1)
    {
        entry tmp = (entry) t1;
        size++;
        list.add(tmp);
    }
    public void update_remove_element(non_playable p1)
    {
        entry e1 = (entry) p1;
        size--;
        list.remove(e1);
    }
    public entry currently_viewer()
    {
        if(size == 0)
        {
            System.out.print("empty list\n");
            return null;
        }
        else
            return list.get(current_index);
    }
    public void show_list()
    {
        for(entry tmp : list)
        {
            if(tmp.type == "image")
            {
                System.out.print(tmp.get_name()+" "+tmp.get_dimension_information()+" "+tmp.get_other_information()+"\n");
            }
            else if(tmp.type == "text")
            {
                System.out.print(tmp.get_name()+" "+tmp.get_other_information()+"\n");
            }
        }
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
            non_playable p1;
            if(current_index < 0)
            {
                System.out.print("previous "+ type+ " couldn't found so current index was reseted\n");
                current_index = 0;   
            }
            else
            {
                for(;current_index>0;current_index--)
                {
                    p1 = (non_playable) this.currently_viewer();
                    if(p1.get_type() == type)
                    {
                        break;
                    }
                }
                p1 = (non_playable) this.currently_viewer();
                if(p1.get_type() != type)
                {
                    System.out.print("previous "+ type+ " couldn't found so current index was reseted\n");
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
            non_playable p1;
            if(current_index == size || current_index > size)
            {
                System.out.print("invalid value.current index was reseted");
                current_index = 0;
            }
            else
            {
                for(;current_index<size-1 ; current_index++)
                {
                    p1 = (non_playable) this.currently_viewer();
                    if(p1.get_type() == type)
                    {
                        break;
                    }
                }
                p1 = (non_playable) this.currently_viewer();
                if(p1.get_type() != type)
                {
                    System.out.print("next "+ type+ " couldn't found so current index was reseted\n");
                    current_index = 0;
                }
            }         
        }
    }

    
    
}

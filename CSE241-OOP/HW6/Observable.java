import java.util.ArrayList;
import java.util.List;
public abstract class Observable {
    private List<Observer> observerList;
    Observable()
    {
        observerList = new ArrayList<>();
    }
    public void register(Observer obs)
    {
        observerList.add(obs);
    }
    public void remove(Observer obs)
    {
        remove(obs);
        observerList.remove(obs);
    }
    public void notification(audio a1)
    {
        for(Observer tmp : observerList)
            tmp.update(a1);
    }
    public void notification(video v1)
    {
        for(Observer tmp : observerList)
            tmp.update(v1);
    }
    public void notification(image i1)
    {
        for(Observer tmp : observerList)
            tmp.update_2(i1);
    }
    public void notification(text t1)
    {
        for(Observer tmp:observerList)
            tmp.update_2(t1);
    }
    public void notification_element(playable p1)
    {
        for(Observer tmp : observerList)
            tmp.update_remove_element(p1);
    }
    public void notification_element(non_playable np1)
    {
        for(Observer tmp : observerList)
            tmp.update_remove_element(np1);
    }


    
}

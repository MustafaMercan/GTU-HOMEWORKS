public interface Observer {
    void update(audio a1);
    void update(video v1);
    void update_2(image i1);
    void update_2(text t1);
    void update_remove_element(playable p1);
    void update_remove_element(non_playable np1);
}

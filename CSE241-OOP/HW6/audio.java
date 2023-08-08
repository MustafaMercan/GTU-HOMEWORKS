public class audio extends entry implements non_visual,playable{
    String audio_name;
    String duration_name;
    String other_information;
    public void info()
    {
        System.out.print(get_name() + " " + get_duration() + " " + get_other_information()+"\n");
    }
    public String get_name(){ return audio_name;}
    public String get_duration(){ return duration_name;}
    public String get_other_information(){ return  other_information;}
    public String get_type(){return type;}
    audio(String name , String duration,String other)
    {
        type = "audio";
        audio_name = name;
        duration_name = duration;
        other_information = other;
    }
}

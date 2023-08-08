public class video extends entry implements playable{
    String video_name;
    String duration_name;
    String other_information;
    //String type;
    
    public void info(){ 
        System.out.print(get_name() + " " + get_duration() + " " + get_other_information()+"\n");
    }
    public String get_name(){ return video_name;}
    public String get_duration(){ return duration_name;}
    public String get_other_information(){ return  other_information;}
    public String get_type(){return type;}
    
    video(String name,String duration,String other)
    {
        type = "video";
        video_name = name;
        duration_name = duration;
        other_information = other;
    }
}

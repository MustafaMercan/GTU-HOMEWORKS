public class text extends entry implements non_playable,non_visual{
    public String text_name;
    public String other_information;
    public void info(){
        System.out.print(get_name() + " " + get_other_information() +"\n");
     }
    text(String name,String other)
    {
        type = "text";
        text_name = name;
        other_information =other;
    }
    public String get_name(){return text_name;}
    public String get_other_information(){return other_information;}
    public String get_type(){return type;}

}

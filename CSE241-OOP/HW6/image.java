public class image extends entry implements non_playable,visual
{
    public String image_name;
    public String dimension_information;
    public String other_information;
    //public String type;

    public void info()
    {
        System.out.print(get_name() + " " + get_dimension_information() +" "+ get_other_information() +"\n");
    }

    public String get_name(){return image_name;}
    public String get_dimension_information(){ return dimension_information;}
    public String get_other_information(){return other_information;}
    public String get_type(){return type;}
    image(String name,String dimension,String other)
    {
        image_name = name;
        dimension_information = dimension;
        other_information = other;
        type = "image";

    }
}

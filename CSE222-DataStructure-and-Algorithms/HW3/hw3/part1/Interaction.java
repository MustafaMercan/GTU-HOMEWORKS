package part1;

public class Interaction extends Post{

    private long interaction_id;

    /**
     * This constructor method allows us to assign the parameters that are received when we first create our object to the variables inside our object.
     * @param current_account_user_name username belonging to the current user
     * @param account_id is account id belonging to the account
     * @param interaction_id is interaction Id belonging to this comment.
     * @param post_id is post ID belonging to the post
     * @param content is the content of the post belonging to the post
     */
    public Interaction(String current_account_user_name,int account_id,long interaction_id,long post_id,String content)
    {
        super(current_account_user_name,account_id,post_id,content);
        this.interaction_id = interaction_id;
    }
    /**
     *It returns the interaction ID 
     */
    public long get_interaction_id(){return this.interaction_id;}
    /**
     * It prints the information related to this interaction.
     */
    public void print_informations(){
        System.out.println("interaction id -> " + this.interaction_id);
        System.out.println("account id -> "+ this.get_account_id());
        System.out.println("post id -> "+ this.get_post_id());
    }
}
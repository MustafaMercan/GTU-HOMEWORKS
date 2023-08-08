package part3;
public class Comment extends Interaction{
    private String content;

    /**
     * This constructor method allows us to assign the parameters that are received when we first create our object to the variables inside our object.
     * @param current_account_user_name username belonging to the current user
     * @param account_id is account id belonging to the account
     * @param interaction_id is interaction Id belonging to this comment.
     * @param post_id is post ID belonging to the post
     * @param post_content is the content of the post belonging to the post
     * @param comment_content is the content of the comment.
     */
    public Comment(String current_account_user_name,int account_id, long interaction_id,long post_id,String post_content,String comment_content)
    {
        super(current_account_user_name,account_id,interaction_id,post_id,post_content);
        this.content = comment_content;
    }
    /**
     * It prints the information related to a comment on the screen.
     */
    public void print_informations()
    {
        System.out.println("'" + this.get_user_name()+ "'" + " said '" + this.content + "'\n");
    }
}
package part2;
public class Like extends Interaction{
    /**
     * This constructor method allows us to assign the parameters that are received when we first create our object to the variables inside our object.
     * @param current_account_user_name username belonging to the current user
     * @param account_id is account id belonging to the account
     * @param interaction_id is interaction Id belonging to this comment.
     * @param post_id is post ID belonging to the post
     * @param content is the content of the post belonging to the post
     */
    public Like(String current_account_user_name,int account_id,long interaction_id,long post_id,String content)
    {
        super(current_account_user_name,account_id,interaction_id,post_id,content);

    }
    /**
     * It prints the information related to this like.
     */
    public void print_informations()
    {

        System.out.print(this.get_user_name()+", ");
    }
}
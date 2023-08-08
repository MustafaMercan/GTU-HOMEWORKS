package part2;
import java.util.LinkedList;
import java.util.Iterator;
public class Post extends Account{
    private long post_id;
    private String content;

    private LinkedList<Like> likes = new LinkedList<Like>();
    // private Like[] likes;

    
    private LinkedList<Comment> comments = new LinkedList<Comment>();
    // private Comment [] comments;
    
    
    /**
     * This constructor method allows us to assign the parameters that are received when we first create our object to the variables inside our object.
     * @param content is the content of the post belonging to the post
     * @param post_id is post ID belonging to the post
     * @param account_id is account id belonging to the account
     * @param user_name username belonging to the current user
     */


    public Post(String content,long post_id,int account_id,String user_name){
        
        super(account_id,user_name);
        this.post_id = post_id;
        this.content = content;
    }
    /**
     * This constructor method allows us to assign the parameters that are received when we first create our object to the variables inside our object.
     * @param current_account_user_name username belonging to the current user
     * @param account_id is account id belonging to the account
     * @param post_id is post ID belonging to the post
     * @param content is the content of the post belonging to the post
     */
    public Post(String current_account_user_name,int account_id, long post_id,String content)
    {
        super(current_account_user_name,account_id);
        this.post_id = post_id;
        this.content = content;

    }
    public LinkedList<Comment> get_all_comment()
    {
        return this.comments;
    }
    public void remove_comment(int index)
    {
        this.comments.remove(index);
    }
    /**
     * It returns the post's id.
     */
    public long get_post_id(){return this.post_id;}
    /**
     * Prints the information belonging to a post.
     */
    public void print_informations(){
        System.out.print("(Post ID :" + this.post_id +") : ");
        System.out.println(this.content);
    }
    /**
     * Adds a like object received as parameter to the like array of the likes .
     * @param new_like holds the like object to be added.
     */
    public void like_post(Like new_like)
    {
        this.likes.add(new_like);
        // int index = 0;
        // while(this.likes[index] != null)
        // {
        //     index++;
        // }
        // this.likes[index] = new_like;
    }
    /**
     * Adds a comment object received as parameter to the comment array of the comments .
     * @param new_comment holds the comment object to be added.
     */
    public void comment_post(Comment new_comment)
    {
        // int index = 0;
        // while(this.comments[index] != null)
        // {
        //     index++;
        // }
        // this.comments[index] = new_comment;
        this.comments.add(new_comment);
    }
    /**
     * Print like interactions belonging to a post to the screen.
     */
    public void get_like_interactions()
    {
        System.out.println("----------------------------");
        System.out.println("(Post ID: " + this.post_id + ") : " + this.content);
        if(this.likes.size() == 0)
        {
            System.out.println("The post no likes.");
            return;
        }
        System.out.print("The post was liked by the following account(s): ");
        for(Like like_element : this.likes)
        {
            like_element.print_informations();
        }
        System.out.print("\n");
        // int index = 0;
        // System.out.println("----------------------------");
        // System.out.println("(Post ID: " + this.post_id + ") : " + this.content);
        // if(this.likes[index] == null)
        // {
        //     System.out.println("The post no likes.");
        //     return;
        // }
        // System.out.print("The post was liked by the following account(s): ");
        // while(this.likes[index] != null)
        // {
        //     this.likes[index].print_informations();
        //     index++;
        // }
        System.out.print("\n");
    }
    /**
     * Print comment interactions belonging to a post to the screen.
     */
    public void get_comment_interactions()
    {
        // int index = 0;
        // if(this.comments[index] == null)
        // {
        //     System.out.println("The post no comments.");
        //     return;       
        // }
        // while(this.comments[index] != null)
        // {
        //     System.out.print("Comment "+ (index+1) + ":");
        //     this.comments[index].print_informations();
        //     index++;
        // }
        int index = 0;
        if(this.comments.size() == 0)
        {
            System.out.println("The post no comments.");
            return;
        }
        for(Comment comment_element : this.comments)
        {
            System.out.print("Comment "+ (index+1) + ":");
            comment_element.print_informations();
            index++;
        }

    }
    /**
     * It returns the post's content.
     */
    public String get_content(){return this.content;}

    /**
     * This method checks whether a liked post has been previously liked by the same user or not
     * @param account_id stores the account ID of the user who performed the like action.
     */
    public boolean check_like_state(int account_id)
    {
        
        for(Like like_element : this.likes)
        {
            if(like_element.get_account_id() == account_id)
                return false;
        }
        return true;
        // int index = 0;
        // while(this.likes[index] != null)
        // {
        //     if(this.likes[index].get_account_id() == account_id)
        //         return false;
        //     index++;
        // }
        // return true;
    }
    public void delete_like(int account_id)
    {

        int index = 0;
        while(index < this.likes.size())
        {
            if(likes.get(index).get_account_id() == account_id)
            {
                this.likes.remove(index);
                return;
            }

            index++;

        }
        // Iterator<Like> iter = this.likes.iterator();
        //  while (iter.hasNext()) 
        //  {
        //     Like like_element = iter.next();
        //     if (like_element.get_account_id() == account_id) {
        //         iter.remove();
        //     }
        // }

    }
}
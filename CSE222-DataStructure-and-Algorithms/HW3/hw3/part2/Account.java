package part2;
import java.util.LinkedList;
public class Account{

    

    private boolean login_state;
    private String user_name;
    private int account_id;
    private String birth_date;
    private String location;

    private LinkedList<Post> posts = new LinkedList<Post>();
    
    private LinkedList<Account> following = new LinkedList<Account>();
    
    private LinkedList<Account> followers = new LinkedList<Account>();

    private LinkedList<Account> blocked_users = new LinkedList<Account>();

    private LinkedList<Message> messages = new LinkedList<Message>();

    private LinkedList<String> history = new LinkedList<String>();

    /**
     * This constructor method allows us to assign the parameters that are received when we first create our object to the variables inside our object.
     * @param account_id is id of new user  account. 
     * @param user_name is name of new user account.
     * @param location is location of new user account.
     * @param birth_date is birthdate of new user account.
     */
    public Account(int account_id,String user_name,String location,String birth_date){

        this.account_id = account_id;
        this.user_name = user_name;
        this.login_state = true;
        this.login_state = false;
        
        this.birth_date = birth_date;
        this.location = location;
    }
    /**
     * This constructor method only assigns values to account_id and user_name variables
     * @param account_id is id of new user account
     * @param user_name is name of new user account
     */
    public Account(int account_id,String user_name){

        this.account_id = account_id;
        this.user_name = user_name;
        this.login_state = true;
        this.login_state = false;
    }
    /**
     * This constructor method only assigns values to account_id and user_name variables
     * @param  account_id is account id of current account.
     * @param current_account_user_name is name of current account.
     */
    public Account(String current_account_user_name,int account_id)
    {
        this.account_id = account_id;
        this.user_name = current_account_user_name; 
    }
    /**
     * This method is returning the username
     */
    public String get_user_name(){return this.user_name;}
    /**
     * This method is returning the account_id
     */
    public int get_account_id(){return this.account_id;}
    /**
     * This method is returning the login_state
     */
    public boolean get_login_state(){return this.login_state;}
    /**
     * This method is set the login_state
     * @param state it determines whether the login_state will be true or false
     */
    public void set_login_state(boolean state){this.login_state = state;}//This method is set the state
    /**
     * When the login process is completed,it sets the login_state to true
     */
    public void login()
    {
        if(!this.check_login_state())
        {
            this.set_login_state(true);
            System.out.println(this.user_name + " logged in the system...\n"); 
        }
        else
            System.out.println("This user is already logged in");
        
    }
     /**
      * When the logout process is completed,it sets the login_state to false
      */
    public void logout()
    {
        System.out.println(this.user_name + " logout in the system\n");
        this.set_login_state(false);
    }

    /**
     * It allows us to print ouıt the information related to the user
     */
    public void print_informations(){
        int count_followers = this.get_count_followers();
        int count_following = this.get_count_following();
        System.out.println("Viewing " + this.user_name +"'s profile...");
        System.out.println("----------------------------------------------");
        System.out.println("ID: " + this.account_id);
        System.out.println("Username: "+ this.user_name);
        System.out.println("Location: "+ this.location);
        System.out.println("Birth date: " + this.birth_date);
        System.out.println(this.user_name + " is following " + count_following + " account(s) and has " + count_followers + "follower(s)");

        if(count_followers != 0)
        {
            System.out.print("The followers of " + this.user_name + " are: ");
            this.print_followers();

        }
        if(count_following != 0)
        {
            System.out.print(this.user_name + " is following: ");
            this.print_follows();
        }

        System.out.println(this.user_name + " has " + this.get_post_num() + " posts\n");
    }
    /**
     * Checking if the user is logged in or not
     */
    public boolean check_login_state()
    {
        if(this.login_state)
            return true;
        return false;
    }
    /**
     * It finds and returns the number of posts shared by the user
     */
    public int get_post_num()
    {
        return this.posts.size();
    }
    
    /**
     * It finds the index of the account that has the same user_name as the user_name pareameter passed to the function.
     * @param user_accounts all created users are stored in this array, which is passed as a parameter.
     * @param user_name it holds the username of the user we are searching for in user_accounts.
     */
    public int find_index_account( LinkedList<Account> user_accounts,String user_name)
    {
        int index = 0;
        for(Account account_element : user_accounts)
        {
            if(account_element.get_user_name().equals(user_name))
                return index;
            index++;
        }
        return -1;
    }
    /**
     * It finds the index of the post that has the same post_id as the post_id pareameter passed to the function.
     * @param user_account It holds the Account object of the user whose posts we are searching for.
     * @param post_id It holds the post_id value of the post we are searching for.
     */ 
    public Post find_post_index(Account user_account, int post_id)
    {
        for(Post post_index : user_account.posts)
        {
            if(post_index.get_post_id() == post_id)
                return post_index;
        }
        return null;
    }
    /**
     * When we look at the profile of any user, it prints out the information related to that user.
     * @param user_accounts all created users are stored in this array, which is passed as a parameter.
     * @param user_name it holds the username of the user whose profile we want to view.
     */ 
    public void view_profile(LinkedList<Account> user_accounts, String user_name)
    {
        if(check_login_state())
        {
            int user_index = this.find_index_account(user_accounts,user_name);
            if(user_index == -1)
            {
                System.out.println("User not found...");
                return;
            }
            if(!check_blocked_account(user_accounts.get(user_index)))
            {
                System.out.println("You have been blocked by the user.");
                return;
            }
            user_accounts.get(user_index).print_informations();
        }
        else
            System.out.println("Please log in");

    }

    /**
     * /When we look at the posts of any user, it prints out the posts's information related to that user.
     * @param user_accounts all created users are stored in this array, which is passed as a parameter.
     * @param user_name it holds the username of the user whose profile we want to view.
     */  
    public void view_user_posts(LinkedList<Account> user_accounts, String user_name)
    {

        if(this.check_login_state())
        {
            int user_index = this.find_index_account(user_accounts,user_name);
            if(user_index == -1)
            {
                System.out.println("User not found.");
                return;
            }
            int index = 0;
            // System.out.println("Viewing "+user_accounts[user_index].get_user_name() +"'s posts...");
            System.out.println("Viewing " + user_accounts.get(user_index).get_user_name() +"'s posts...");
            if(user_accounts.get(user_index).posts.isEmpty())
            {
                System.out.println(user_accounts.get(user_index).get_user_name()+ " does not have any posts.");
                return ;
            }
            for(Post user_post : user_accounts.get(user_index).posts)
            {
                user_post.print_informations();
            }
            System.out.print("\n");
        }
        else
            System.out.println("Please log in");

    }
    /**
     * It finds the number of users that the given user is following.
     */  
    
    public int get_count_following(){
        // int index = 0;
        // while(this.following[index] != null)
        //     index++;
        return this.following.size();
    }
    /**
     * It finds the number of users who are following the given user 
     */  
    public int get_count_followers(){
        return this.followers.size();
    }
    /**
     * It allows the user to create a new post.
     */  
    public void create_new_post(String content,long post_id)
    {
        if(this.check_login_state())
        {
            System.out.println("Post is creating...\n");
            Post new_post = new Post(content,post_id,this.account_id,this.user_name);
            posts.add(new_post);
        }
        else
            System.out.println("Please log in");
    }

    /**
     * It allows the user to follow another user
     * @param user_accounts all created users are stored in this array, which is passed as a parameter.
     * @param user_name it holds the username of the user we want to follow.
     */ 
    public void follow_someone(LinkedList<Account> user_accounts,String user_name)
    {
        
        if(this.check_login_state())
        {
            int user_index = this.find_index_account(user_accounts,user_name);
            if(user_index == -1)
            {
                System.out.println("User not found...");
                return;
            }
            if(user_accounts.get(user_index).get_user_name().equals(this.user_name))
            {
                System.out.println("You cannot follow yourself...");
                return;
            }
            if(!check_blocked_account(user_accounts.get(user_index)))
            {
                System.out.println("You have been blocked by the user.");
                return;

            }
            else if(this.check_follow_state(user_accounts.get(user_index)))
            {
                System.out.println("Following " + user_accounts.get(user_index).get_user_name() + "...\n");
                int index = 0;
                following.add(user_accounts.get(user_index));
                history.add("You followed " + user_accounts.get(user_index).get_user_name());
                user_accounts.get(user_index).add_follower(this);
            }
            else
                System.out.println("You already followed this user before");

        }
        else
            System.out.println("Please log in");
    }
    public void unfollow_someone(LinkedList<Account> user_accounts,String user_name)
    {
        if(this.check_login_state())
        {
            int user_index = this.find_index_account(user_accounts,user_name);
            if(user_index == -1)
            {
                System.out.println("User not found...");
                return;
            }
            if(user_accounts.get(user_index).get_user_name().equals(this.user_name))
            {
                System.out.println("You cannot unfollow yourself...");
                return;
            }
            if(!this.check_follow_state(user_accounts.get(user_index)))
            {
                int index = 0;
                while(index < this.following.size())
                {
                    if(this.following.get(index).get_account_id() == user_accounts.get(user_index).get_account_id())
                    {
                        System.out.println("Unfollowing "+user_accounts.get(user_index).get_user_name());
                        System.out.println("You unfollowed "+user_accounts.get(user_index).get_user_name());
                        following.remove(index);
                        user_accounts.get(user_index).remove_follower(this);
                        history.add("You unfollowed " + user_accounts.get(user_index).get_user_name());

                        return; 
                    }
                    index++;
                }
            }
            else
            {
                System.out.println("You already not followed this user before");
                return;
            }

        }
        else
             System.out.println("Please log in");
            
    }

    public void unfollow_someone(LinkedList<Account> user_accounts,String user_name, boolean flag)
    {

            int user_index = this.find_index_account(user_accounts,user_name);
            if(user_index == -1)
            {
                System.out.println("User not found...");
                return;
            }
            if(user_accounts.get(user_index).get_user_name().equals(this.user_name))
            {
                System.out.println("You cannot unfollow yourself...");
                return;
            }
            if(!this.check_follow_state(user_accounts.get(user_index)))
            {
                int index = 0;
                while(index < this.following.size())
                {
                    if(this.following.get(index).get_account_id() == user_accounts.get(user_index).get_account_id())
                    {
                        System.out.println("Unfollowing "+user_accounts.get(user_index).get_user_name());
                        System.out.println("You unfollowed "+user_accounts.get(user_index).get_user_name());
                        following.remove(index);
                        user_accounts.get(user_index).remove_follower(this);
                        history.add("You unfollowed " + user_accounts.get(user_index).get_user_name());

                        return; 
                    }
                    index++;
                }
            }
            else
            {
                System.out.println("You already not followed this user before");
                return;
            }

        

            
    }
    /**
     * This method checks whether the user being followed has been followed before or not.
     * @param follow_user is acccount object of the user being followed.
     */

    public boolean check_follow_state(Account follow_user)
    {

        for(Account account_element : follow_user.followers)
        {
            if(account_element.get_account_id() == this.account_id)
                return false;
        }
        return true;
    }

    public boolean check_follower_state(Account user)
    {
        for(Account account_element : user.following)
        {
            if(account_element.get_account_id() == this.account_id)
                return false;
        }
        return true;
    }
    /**
     * It adds the current account to the followers of t he user whose profile we are following.
     * @param current_account It holds the Account object of the current user.
     */ 
    public void add_follower(Account current_account)
    {
        this.followers.add(current_account);
    }
    public void remove_follower(Account current_account)
    {
        int index = 0;
        while(index < this.followers.size())
        {
            if(this.followers.get(index).get_account_id() ==current_account.get_account_id())
            {
                this.followers.remove(index);
                return ;
            }
            index++;
        }
    }
    /**
     * It prints out the information related to the followers.
     */ 
    public void print_followers()
    {
        for(Account follower : this.followers)
        {
            System.out.print(follower.get_user_name() +",");
        }
        System.out.print("\n");

    }
    /**
     * It prints out the information related to the following.
     */ 
    public void print_follows()
    {
        for(Account following_user : this.following)
        {
            System.out.print(following_user.get_user_name() + ",");
        }
        System.out.print("\n");
    }
    /**
     * It finds the index where a specific post_id belonging to the user is stored.
     * @param post_id it holds the id of the post belonging to the current user.
     */ 

    /**
     * Allows us to like any user's post
     * @param user_accounts all created users are stored in this array, which is passed as a parameter.
     * @param user_name it holds the username of the user whose post we want to like
     * @param post_id it holds the post_id value of the post we want to like
     */ 
    public void unlike_a_post(LinkedList<Account> user_accounts,String user_name, int post_id)
    {
        if(this.check_login_state())
        {
            int user_index = this.find_index_account(user_accounts,user_name);
            if(user_index == -1)
            {
                System.out.println("User not found");
                return ;
            }
            Post current_post = find_post_index(user_accounts.get(user_index),post_id);
            if(current_post == null)
            {
                System.out.println("Post not found");
                return ;
            }
            if(!current_post.check_like_state(this.account_id))
            {
                System.out.println("Unlike process completed");
                current_post.delete_like(this.account_id);
            }
            else
            {
                System.out.println("You've already unliked this post");
            }

        }
        else
        {
            System.out.println("Please Log in");

        }
    }
    public void like_a_post(LinkedList<Account> user_accounts,String user_name, int post_id)
    {
        if(this.check_login_state())
        {
            int user_index = this.find_index_account(user_accounts,user_name);
            if(user_index == -1)
            {
                System.out.println("User not found");
                return;
            }
            Post current_post = find_post_index(user_accounts.get(user_index),post_id);
            if(current_post == null)
            {
                System.out.println("Post not found");
                return ;
            }
            if(current_post.check_like_state(this.account_id))
            {
                System.out.println("Like was created\n");
                long unique_number = System.currentTimeMillis();
                Like new_like = new Like(this.user_name,this.account_id,unique_number,current_post.get_post_id(),current_post.get_content());
                current_post.like_post(new_like);
                history.add("You liked " + user_name + "'s post id: " + post_id);
            }
            else
                System.out.println("You're already like this post");
        }
        else
            System.out.println("Please log in");
        

    }
    /**
     * Allows us to add a comment to any user's post
     * @param user_accounts all created users are stored in this array, which is passed as a parameter.
     * @param post_id it holds the post_id value of the post we want to like
     * @param content contains the content of the comment we want to make
     */ 
    public void add_comment_post(LinkedList<Account> user_accounts,long post_id,String content)
    {
        int user_index = 0;
        int post_index = 0;

        if(this.check_login_state())
        {
            for(Account account_element : user_accounts)
            {
                for(Post post_element : account_element.posts )
                {
                    if(post_element.get_post_id() == post_id)
                    {
                        if(!this.check_blocked_account(account_element))
                        {
                            System.out.println("BLOCKED");
                            return;
                        }
                        else
                        {
                            System.out.println("Comment was created\n");
                            long unique_number = System.currentTimeMillis();
                            Comment new_comment = new Comment(this.user_name,this.account_id,unique_number,post_element.get_post_id(),post_element.get_content(),content);
                            post_element.comment_post(new_comment);
                            history.add("You commented gokhankaya's post id : " + post_id);
                            return;
                        }

                    }     
                }
            }
            System.out.println("The post cannot found.");
        }
        else
            System.out.println("Please log in!");
    }

    /**
     * Prints all the interactions of the user we are viewing on the screen
     * @param user_accounts all created users are stored in this array, which is passed as a parameter.
     * @param user_name the username of the user whose interactions we want to examine
    
     */
    public void get_all_interactions(LinkedList<Account> user_accounts, String user_name)
    {
        if(this.check_login_state())
        {
            int user_index = this.find_index_account(user_accounts,user_name);
            if(user_index == -1)
            {
                System.out.println("User cannot found...");
                return;
            }
            Account viewing_user = user_accounts.get(user_index);
            System.out.println("Viewing " + viewing_user.get_user_name() + "'s posts's interactions...");
            if(viewing_user.posts.size() == 0)
            {
                System.out.println("Thera are no like interactions on " + viewing_user.get_user_name() +"'s profile.");
                return;
            }
            for(Post post_element : viewing_user.posts)
            {
                post_element.get_like_interactions();
                post_element.get_comment_interactions();
                System.out.print("\n");
            }
        } 
        else
            System.out.println("Please log in");

    }
    public void show_history()
    {
        if(this.check_login_state())
        {
            System.out.println("\nYour history\n");
            int index = 0;
            for(String string_element : history)
            {
                System.out.println(string_element);
            }

        }
        else
            System.out.println("Please log in");
    }
    public void uncomment_post(LinkedList<Account> user_accounts, String user_name,long post_id)
    {
        if(this.check_login_state())
        {
            int user_index = this.find_index_account(user_accounts,user_name);
            if(user_index==-1)
            {
                System.out.println("User cannot found...");
                return;
            }
            Account viewing_user = user_accounts.get(user_index);
            int index = 0;
            for(Post post_element : user_accounts.get(user_index).posts)
            {
                if(post_element.get_post_id() == post_id)
                {
                    for(Comment comment_element : post_element.get_all_comment())
                    {
                        if(comment_element.get_account_id() == this.account_id)
                        {
                            history.add("You uncomment " + user_name + "'s post id: " + post_id);
                            post_element.remove_comment(index);
                            return;
                        }
                        index++;
                    }
                }
            }

        }
        else
            System.out.println("Please log in");
    }

    /**
     * Allows us to send a message to a user
     * @param user_accounts all created users are stored in this array, which is passed as a parameter.
     * @param user_name the username of the user we want to send a message to
     * @param message_id  message ID number for the message we will send
     * @param message_content the content of the message we want to send.
     */
    public void send_message(LinkedList<Account> user_accounts, String user_name, long message_id, String message_content)
    {

        if(this.check_login_state())
        {
            int index = find_index_account(user_accounts,user_name);
            if(index == -1)
            {
                System.out.println("The user cannot found...");
                return ;
            }
            if(this.user_name.equals(user_name))
            {
                System.out.println("You cannot send a message yourself!");
                return;
            }
            Account receiver_account = user_accounts.get(index);
            if(!this.check_blocked_account(receiver_account))
            {
                System.out.println("You have been blocked by the user.");
                return;
            }
            System.out.println("Message was sended \n");
            Message new_message_receiver = new Message(message_id,(long)this.account_id,(long)receiver_account.get_account_id(),message_content,this.user_name);
            Message new_message_sender = new Message(message_id,(long)this.account_id,(long)receiver_account.get_account_id(),message_content,receiver_account.get_user_name());
            receiver_account.add_message(new_message_receiver);
            this.add_message(new_message_sender);
        }
        else
            System.out.println("Please log in");
        

    
    }
    /**
     * Adds the created message object to the messages array inside the account
     * @param new_message the new message object to be added
     */
    public void add_message(Message new_message)
    {
        this.messages.add(new_message);
    }
    /**
     *prints the messages in the inbox
     */
    public void print_inbox_messages()
    {
        if(this.check_login_state())
        {

            for(Message message_element : this.messages)
            {
                if(message_element.get_receiver_id() == (long)this.account_id)
                {
                    System.out.println("Message ID: " + message_element.get_message_id());
                    System.out.println("From: " + message_element.get_user_name());
                    System.out.println("To: "+ this.user_name);
                    System.out.println("Message: "+ message_element.get_message_content());
                    System.out.println("\n");
                }
            }
        }
        else
            System.out.println("Please log in");

    }
    /**
     *prints the messages in the inbox
     */
    public void print_outbox_messages()
    {
        if(this.check_login_state())
        {

            for(Message message_element : this.messages)
            {
                if(message_element.get_receiver_id() == (long)this.account_id)
                {
                    System.out.println("Message ID: " + message_element.get_message_id());
                    System.out.println("From: " + this.user_name);
                    System.out.println("To: "+ message_element.get_user_name());
                    System.out.println("Message: "+ message_element.get_message_content());
                    System.out.println("\n");
                }
            }
        }
        else
            System.out.println("Please log in");

    }
    /**
     * Determines the number of messages in the inbox
     */
    public void check_inbox()
    {
        if(this.check_login_state())
        {
            int index = 0;
            int count = 0;

            for(Message message_element : this.messages)
            {
                if(message_element.get_receiver_id() == (long)this.account_id)
                    count++;
                index++;
            }
            System.out.println("Checking inbox...");
            System.out.println("There is/are "+ count + " message(s) in the inbox\n");
        }
        else
            System.out.println("Please log in");

    }
    /**
     * Determines the number of messages in the outbox
     */
    public void check_outbox()
    {
        if(this.check_login_state())
        {
            int index = 0;
            int count = 0;
            for(Message message_element : this.messages)
            {
                if(message_element.get_receiver_id() != (long)this.account_id)
                    count++;
                index++;
            }
            System.out.println("Checking outbox...");
            System.out.println("There is/are "+ count + " message(s) in the outbox\n");
        }
        else
            System.out.println("Please log in");
    }
    /**
     * This method allows blocking a user
     * @param user_accounts all created users are stored in this array, which is passed as a parameter.
     * @param user_name is the username of the user to be blocked
     */


    /*
    public void block_someone(LinkedList<Account> user_accounts, String user_name)
    {
        int user_index = this.find_index_account(user_accounts,user_name);
        int index = 0;
        if(user_index == -1)
        {
            System.out.println("User cannot found.");
            return;
        }
        if(user_name == this.user_name)
        {
            System.out.println("You cannot block to yourself!!");
            return;
        }
        if(!check_blocked_account(user_accounts.get(user_index)))
        {
            System.out.println("You have been blocked by the user.");
            return ;

        }
        System.out.println("You blocked to " + user_name + "\n");
        this.blocked_users.add(user_accounts.get(user_index));
    }*/

    public void block_someone(LinkedList<Account> user_accounts, String user_name)
    {
        int user_index = this.find_index_account(user_accounts,user_name);
        int index = 0;
        if(user_index == -1)
        {
            System.out.println("User cannot found.");
            return;
        }
        if(user_name == this.user_name)
        {
            System.out.println("You cannot block to yourself!!");
            return;
        }
        if(!check_blocked_account(user_accounts.get(user_index)))
        {
            System.out.println("You have been blocked by the user.");
            return ;
        }

        
            if(!this.check_follow_state(user_accounts.get(user_index)) || !this.check_follower_state(user_accounts.get(user_index)))
            {
                if(!this.check_follow_state(user_accounts.get(user_index)))
                {
                        System.out.println("You blocked to " + user_name + "\n");
                        this.unfollow_someone(user_accounts,user_accounts.get(user_index).get_user_name());
                        this.blocked_users.add(user_accounts.get(user_index));
                }
                if(!this.check_follower_state(user_accounts.get(user_index)))
                {
                        user_accounts.get(user_index).unfollow_someone(user_accounts,this.user_name,true);
                        System.out.println("You blocked to " + user_name + "\n");
                        this.blocked_users.add(user_accounts.get(user_index));
                }
            }
            else
            {
                while(index < this.following.size())
                {
                    if(this.following.get(index).get_account_id() == user_accounts.get(user_index).get_account_id())
                    {
                        System.out.println("You blocked to " + user_name + "\n");
                        following.remove(index);
                        user_accounts.get(user_index).remove_follower(this);
                        history.add("You unfollowed " + user_accounts.get(user_index).get_user_name());
                        return; 
                    }
                    index++;
                }
            }
        if(!this.check_follow_state(user_accounts.get(user_index)) || !this.check_follower_state(user_accounts.get(user_index)) )
        {
                    this.unfollow_someone(user_accounts,user_accounts.get(user_index).get_user_name());
                    System.out.println("You blocked to " + user_name + "\n");
                    this.blocked_users.add(user_accounts.get(user_index));
        }
        else
        {
                while(index < this.following.size())
                {
                    if(this.following.get(index).get_account_id() == user_accounts.get(user_index).get_account_id())
                    {
                        System.out.println("You blocked to " + user_name + "\n");
                        following.remove(index);
                        user_accounts.get(user_index).remove_follower(this);
                        history.add("You unfollowed " + user_accounts.get(user_index).get_user_name());

                        return; 
                    }
                    index++;
                }
        }


        

    }


    /*
        if(this.check_follow_state(user_accounts.get(user_index)))
    */

    /**
     * This method allows blocking a user
     * @param user_accounts all created users are stored in this array, which is passed as a parameter.
     * @param user_name is the username of the user to be blocked
     */
    public void unblock_someone(LinkedList<Account> user_accounts, String user_name)
    {
        int user_index = this.find_index_account(user_accounts,user_name);
        int index = 0;
        if(user_index == -1)
        {
            System.out.println("User cannot found");
        }
        while(index < this.blocked_users.size())
        {
            if(this.blocked_users.get(index).get_account_id() == user_accounts.get(user_index).get_account_id())
            {
                System.out.println("The unblock of the user name " + user_accounts.get(user_index).get_user_name()+" has been unblocked");
                this.blocked_users.remove(index);
                return;
            }
            index++;
        }
        System.out.println("You haven't already blocked someone like that");

    }
    /**
     * This method checks whether the user has been blocked or not.
     * @param receiver_account is the account object of the user that is being checked.
     */
    public boolean check_blocked_account(Account receiver_account)
    {
        for(Account blocked_element : receiver_account.blocked_users)
        {
            if(blocked_element.get_account_id() == this.account_id)
                return false;
        }
        return true;
    }
}
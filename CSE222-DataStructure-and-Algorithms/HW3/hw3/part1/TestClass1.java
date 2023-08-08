package part1;
import java.util.ArrayList;



public class TestClass1{

    public static void main(String[] args)
    {

        long startTime = System.currentTimeMillis();
        // Account [] user_accounts = new Account[100];
        // Step 1 -> Creating 3 accounts...
        Account gizemsungu = new Account(0,"gizemsungu","Istanbul","11.11.2000");
        Account sibelgulmez = new Account(1,"sibelgulmez","Istanbul","11.11.2000");
        Account gokhankaya = new Account(2,"gokhankaya","Istanbul","11.11.2000");
        // We are adding the newly created account objects to ArrayList in order.
        ArrayList<Account> user_accounts = new ArrayList<Account>();

        user_accounts.add(gizemsungu);
        user_accounts.add(sibelgulmez);
        user_accounts.add(gokhankaya);
        // Step 2 -> Logging into an account (username: sibelgulmez).
        sibelgulmez.login();
        // Step 3 -> Sharing two posts...
        sibelgulmez.create_new_post("I like Java.",0);
        sibelgulmez.create_new_post("Java the coffe...",1);
        //Step 4 -> Following gizemsungu and gokhankaya...
        sibelgulmez.follow_someone(user_accounts,"gizemsungu");
        sibelgulmez.follow_someone(user_accounts,"gokhankaya");
        // Step 5 -> Logging out from account 'sibelgulmez';
        sibelgulmez.logout();
        // Step 6 -> Logging into another account (username:gokhankaya)
        gokhankaya.login(); 
        // Step 7 -> Viewing sibelgulmez profile...
        // If you try to view profile a non-existent user, you will encounter an error message saying that the user cannot be found.
        gokhankaya.view_profile(user_accounts,"sibelgulmez");
        // Step 8 -> Viewing sibelgulmez' posts...
        gokhankaya.view_user_posts(user_accounts,"sibelgulmez");
        //Step 9 -> Liking a post of sibelgulmez.
        gokhankaya.like_a_post(user_accounts,"sibelgulmez",0);
        // Step 10 -> Adding a comment on a post of sibelgulmez...
        gokhankaya.add_comment_post(user_accounts,0,"me too...");
        // Step 11 -> following sibelgulmez and gizemsungu...
        gokhankaya.follow_someone(user_accounts,"sibelgulmez");
        gokhankaya.follow_someone(user_accounts,"gizemsungu");
        // Step12 -> Sending a message to gizemsungu...
        //You cannot send a message to yourself.If you send you will take a error message.
        gokhankaya.send_message(user_accounts,"gizemsungu",0,"This homework is too easy!");
        // Step 13 -> Logging out from account 'gokhankaya'
        gokhankaya.logout();
        // Step 14 -> Logging into another account (username:gizemsungu)
        gizemsungu.login();
        // Step 15 -> Checking outbox...
        gizemsungu.check_outbox();
        // Step 16 -> Checking inbox...
        gizemsungu.check_inbox();
        // Step 17 -> Viewing inbox...
        gizemsungu.print_inbox_messages();
        // Step 18 -> Viewing sibelgulmez's profile
        gizemsungu.view_profile(user_accounts,"sibelgulmez");
        // Step 19 -> Viewing sibelgulmez's posts...
        gizemsungu.view_user_posts(user_accounts,"sibelgulmez");
        // Step 20 -> Viewing sibelgulmez's posts' interactions...
        gizemsungu.get_all_interactions(user_accounts,"sibelgulmez");
        // Step 21 -> Liking sibelgulmez's posts...
        gizemsungu.like_a_post(user_accounts,"sibelgulmez",0);
        gizemsungu.like_a_post(user_accounts,"sibelgulmez",1);
        // Step 22 -> Viewing sibelgeulmez's posts' interactions...
        gizemsungu.get_all_interactions(user_accounts,"sibelgulmez");
        gizemsungu.logout();

        long endtime = System.currentTimeMillis();
        float result = (endtime-startTime);
        result /=  10000.0f;
        System.out.println("running times -> " + (result));
    }


}

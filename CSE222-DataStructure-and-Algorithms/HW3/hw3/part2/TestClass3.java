package part2;
import java.util.LinkedList;

public class TestClass3{
    public static void main(String [] args)
    {

        long startTime = System.currentTimeMillis();
        
        Account gizemsungu = new Account(0,"gizemsungu","Istanbul","11.11.2000");
        Account sibelgulmez = new Account(1,"sibelgulmez","Istanbul","11.11.2000");
        Account gokhankaya = new Account(2,"gokhankaya","Istanbul","11.11.2000");

        LinkedList<Account> user_accounts = new LinkedList<Account>();
        user_accounts.add(gizemsungu);
        user_accounts.add(sibelgulmez);
        user_accounts.add(gokhankaya);

    
        //SCENERIO 1
        // Step 2 -> Logging into an account (username: sibelgulmez).
        // If we try to perform any operation without logging in, the program will display an error message.
        // If we try to log in again while our account is already open, we will encounter an error message again.
        sibelgulmez.login();
        // Step 3 -> Sharing two posts..

        sibelgulmez.create_new_post("I like Java.",0);
        sibelgulmez.create_new_post("Java the coffe...",1);
        //Step 4 -> Following gizemsungu and gokhankaya...
        // If you try to follow a non-existent user, you will encounter an error message saying that the user cannot be found.
        // If you try to follow yourself, you will encounter an error message saying that you cannot follow yourself.
        sibelgulmez.follow_someone(user_accounts,"gizemsungu");
        sibelgulmez.follow_someone(user_accounts,"gokhankaya");
        // Step 5 -> Logging out from account 'sibelgulmez';
        sibelgulmez.logout();
        // Step 6 -> Logging into another account (username:gokhankaya)
        gokhankaya.login(); 
        // Step 7 -> Viewing sibelgulmez profile..
        // If you try to view profile a non-existent user, you will encounter an error message saying that the user cannot be found.
        gokhankaya.view_profile(user_accounts,"sibelgulmez");
        // Step 8 -> Viewing sibelgulmez' posts...
        // If you try to view user posts a non-existent user, you will encounter an error message saying that the user cannot be found.
        gokhankaya.view_user_posts(user_accounts,"sibelgulmez");
        //Step 9 -> Liking a post of sibelgulmez.
        // If you try to like a post of non-existent user, you will encounter an error message saying that the user cannot be found.
        // If you send a non-existendt post Id , you will encoutner an error message again.
        // // If the user is already like the same post, an error message will be displayed
        gokhankaya.like_a_post(user_accounts,"sibelgulmez",0);
        // Step 10 -> Adding a comment on a post of sibelgulmez...
        // If you send a non-existendt post Id , you will encoutner an error message again.
        gokhankaya.add_comment_post(user_accounts,0,"me too...");
        // Step 11 -> following sibelgulmez and gizemsungu...
        gokhankaya.follow_someone(user_accounts,"sibelgulmez");
        gokhankaya.follow_someone(user_accounts,"gizemsungu");
        // Step12 -> Sending a message to gizemsungu...
        //You cannot send a message to yourself.If you send you will take a error message.
        gokhankaya.send_message(user_accounts,"gizemsungu",0,"This homework iş too easy!");
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
        



        //SCNERIO 2
        gizemsungu.login();
        gizemsungu.create_new_post("Post1",2);
        gizemsungu.create_new_post("Post2",3);
        gizemsungu.logout();


        sibelgulmez.login();
        sibelgulmez.view_profile(user_accounts,"gizemsungu");
        sibelgulmez.like_a_post(user_accounts,"gizemsungu",2);
        sibelgulmez.logout();

        gokhankaya.login();
        gokhankaya.view_profile(user_accounts,"gizemsungu");
        gokhankaya.add_comment_post(user_accounts,3,"Nice!");
        gokhankaya.send_message(user_accounts,"gizemsungu",1,"Hello");
        gokhankaya.logout();

        gizemsungu.login();
        gizemsungu.view_profile(user_accounts,"gizemsungu");
        gizemsungu.print_inbox_messages();
        gizemsungu.logout();


        //SCNERIO 3

        System.out.println("SENARYO 3 FALAN \n\n\n");
        
        gizemsungu.login();
        gizemsungu.block_someone(user_accounts,"sibelgulmez");
        gizemsungu.logout();

        sibelgulmez.login();
        sibelgulmez.view_profile(user_accounts,"gizemsungu");
        sibelgulmez.send_message(user_accounts,"gizemsungu",10,"blocked message");




        //Error cases
        //If the user tries to log in again without logging out, they will encounter an error message.
        gizemsungu.login();
        gizemsungu.login();

        //User cannot send messages to themselves or follow themselves.
        gizemsungu.follow_someone(user_accounts,"gizemsungu");
        gizemsungu.send_message(user_accounts,"gizemsungu",6,"I cannot send a message to myself");
    
        // An error message is displayed when an invalid username is entered.
        gizemsungu.view_profile(user_accounts,"nonexistuser");
        gizemsungu.follow_someone(user_accounts,"nonexistuser");
        gizemsungu.send_message(user_accounts,"nonexistuser",6,"I cannot send a message to myself");
        
        //The user cannot perform any action without logging in.
        gokhankaya.follow_someone(user_accounts,"gizemsungu");


        long endtime = System.currentTimeMillis();
        float result = (endtime-startTime);
        result /=  10000.0f;
        System.out.println("running times -> " + (result));


    }

}
package homework1;

public class TestClass1{

    public static void main(String[] args)
    {

        Account [] user_accounts = new Account[100];
        // Step 1 -> Creating 3 accounts...
        Account gizemsungu = new Account(0,"gizemsungu","Istanbul","11.11.2000");
        Account sibelgulmez = new Account(1,"sibelgulmez","Istanbul","11.11.2000");
        Account gokhankaya = new Account(2,"gokhankaya","Istanbul","11.11.2000");
        // We are adding the newly created account objects to array in order.
        user_accounts[0] = gizemsungu;
        user_accounts[1] = sibelgulmez;
        user_accounts[2] = gokhankaya;
        // Step 2 -> Logging into an account (username: sibelgulmez).
        // If we try to perform any operation without logging in, the program will display an error message.
        // If we try to log in again while our account is already open, we will encounter an error message again.
        sibelgulmez.login();
        // Step 3 -> Sharing two posts...
        // create_new_post take two parameter.
        // 1-> post content
        // 2-> post id number
        sibelgulmez.create_new_post("I like Java.",0);
        sibelgulmez.create_new_post("Java the coffe...",1);
        //Step 4 -> Following gizemsungu and gokhankaya...
        //follow_someone method take two parameter
        // 1-> Accounts Array
        // 2-> the username of the user we want to follow.
        // If you try to follow a non-existent user, you will encounter an error message saying that the user cannot be found.
        // If you try to follow yourself, you will encounter an error message saying that you cannot follow yourself.
        sibelgulmez.follow_someone(user_accounts,"gizemsungu");
        sibelgulmez.follow_someone(user_accounts,"gokhankaya");
        // Step 5 -> Logging out from account 'sibelgulmez';
        sibelgulmez.logout();
        // Step 6 -> Logging into another account (username:gokhankaya)
        gokhankaya.login(); 
        // Step 7 -> Viewing sibelgulmez profile...
        // view_profile take two parameter
        // 1-> Accounts Array
        // 2-> the username of the user we want to view profile.
        // If you try to view profile a non-existent user, you will encounter an error message saying that the user cannot be found.
        gokhankaya.view_profile(user_accounts,"sibelgulmez");
        // Step 8 -> Viewing sibelgulmez' posts...
        // view_user_posts take two parameter
        // 1-> Accounts Array
        // 2-> the username of the user we want to view posts.
        // If you try to view user posts a non-existent user, you will encounter an error message saying that the user cannot be found.
        gokhankaya.view_user_posts(user_accounts,"sibelgulmez");
        //Step 9 -> Liking a post of sibelgulmez.
        // view_user_posts take three parameter
        // 1-> Accounts Array
        // 2-> the username of the user whose post we want to like.
        // 3-> the post id of the post we want to like 
        // If you try to like a post of non-existent user, you will encounter an error message saying that the user cannot be found.
        // If you send a non-existendt post Id , you will encoutner an error message again.
        // // If the user is already like the same post, an error message will be displayed
        gokhankaya.like_a_post(user_accounts,"sibelgulmez",0);
        // Step 10 -> Adding a comment on a post of sibelgulmez...
        // It is take three parameter
        // 1-> Accounts Array
        // 2-> Post ID
        // 3-> message content
        // If you send a non-existendt post Id , you will encoutner an error message again.
        gokhankaya.add_comment_post(user_accounts,0,"me too...");
        // Step 11 -> following sibelgulmez and gizemsungu...
        // If the user is already following the same account, an error message will be displayed
        gokhankaya.follow_someone(user_accounts,"sibelgulmez");
        gokhankaya.follow_someone(user_accounts,"gizemsungu");
        // Step12 -> Sending a message to gizemsungu...
        //It take four parameter
        // 1-> Accounts Array
        // 2-> Receiver user name
        // 3-> Message ID
        // 4-> Message content
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
    }


}

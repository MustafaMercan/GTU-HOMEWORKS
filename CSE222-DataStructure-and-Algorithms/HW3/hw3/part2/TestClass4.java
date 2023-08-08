package part2;
import java.util.LinkedList;

public class TestClass4{
    public static void main(String[] args)
    {

      long startTime = System.currentTimeMillis();

        LinkedList<Account> user_accounts = new LinkedList<Account>();

        Account test0 = new Account(0,"test0","Istanbul","11.11.2000");
        Account test1 = new Account(1,"test1","Istanbul","11.11.2000");
        Account test2 = new Account(2,"test2","Istanbul","11.11.2000");
        Account test3 = new Account(3,"test3","Istanbul","11.11.2000");
        Account test4 = new Account(4,"test4","Istanbul","11.11.2000");
        Account test5 = new Account(5,"test5","Istanbul","11.11.2000");
        Account test6 = new Account(6,"test6","Istanbul","11.11.2000");
        Account test7 = new Account(7,"test7","Istanbul","11.11.2000");
        Account test8 = new Account(8,"test8","Istanbul","11.11.2000");
        Account test9 = new Account(9,"test9","Istanbul","11.11.2000");

        user_accounts.add(test0);
        user_accounts.add(test1);
        user_accounts.add(test2);
        user_accounts.add(test3);
        user_accounts.add(test4);
        user_accounts.add(test5);
        user_accounts.add(test6);
        user_accounts.add(test7);
        user_accounts.add(test8);
        user_accounts.add(test9);
 
     /*=========================================================================*/

        test0.login();

        test0.create_new_post("Test 0 user posted test 0",0);
        test0.create_new_post("Test 0 user posted test 1",1);
        test0.follow_someone(user_accounts,"test1");
        test0.follow_someone(user_accounts,"test2");
        test0.follow_someone(user_accounts,"test3");
        test0.follow_someone(user_accounts,"test4");
        test0.follow_someone(user_accounts,"test5");
        test0.add_comment_post(user_accounts,0,"i commented myself 1 xd");
        test0.add_comment_post(user_accounts,0,"i commented myself 2 xd");
        test0.view_profile(user_accounts,"test1");
        test0.send_message(user_accounts,"test1",0,"hi test1 im test 0 and this is my first message.");
        test0.block_someone(user_accounts,"test2");
        test0.block_someone(user_accounts,"test3");
        test0.block_someone(user_accounts,"test5");
        test0.block_someone(user_accounts,"test8");
        test0.unblock_someone(user_accounts,"test3");
        test0.show_history();
        
        test0.logout();

     /*=========================================================================*/

        test1.login();
        test1.like_a_post(user_accounts,"test0",0);
        test1.like_a_post(user_accounts,"test0",1);
        test1.logout();


     /*=========================================================================*/

        test2.login();

        test2.follow_someone(user_accounts,"test0");


        test2.create_new_post("Test2 user posted test 0",2);
        test2.create_new_post("Test2 user posted test 1",3);
        test2.create_new_post("Test2 user posted test 2",4);
        test2.create_new_post("Test2 user posted test 3",5);
        test2.create_new_post("Test2 user posted test 4",6);
        test2.create_new_post("Test2 user posted test 5",7);
        test2.create_new_post("Test2 user posted test 6",8);
        test2.create_new_post("Test2 user posted test 7",9);


        test2.send_message(user_accounts,"test0",1,"please unblock me !!!");

        test2.show_history();
        test2.logout();


    /*=========================================================================*/
        test3.login();

        test3.add_comment_post(user_accounts,4,"test");
        test3.add_comment_post(user_accounts,4,"test");
        test3.add_comment_post(user_accounts,4,"test");
        test3.add_comment_post(user_accounts,4,"test");
        test3.add_comment_post(user_accounts,4,"test");
        test3.add_comment_post(user_accounts,4,"test");
        test3.add_comment_post(user_accounts,4,"test");
        test3.add_comment_post(user_accounts,4,"test");
        test3.uncomment_post(user_accounts,"test2",4);
        test3.uncomment_post(user_accounts,"test2",4);
        test3.uncomment_post(user_accounts,"test2",4);
        test3.uncomment_post(user_accounts,"test2",4);
        test3.uncomment_post(user_accounts,"test2",4);
        test3.like_a_post(user_accounts,"test2",2);
        test3.like_a_post(user_accounts,"test2",3);
        test3.like_a_post(user_accounts,"test2",4);
        test3.like_a_post(user_accounts,"test2",5);
        test3.unlike_a_post(user_accounts,"test2",2);
        test3.unlike_a_post(user_accounts,"test2",3);
        test3.show_history();

        test3.logout();


    /*=========================================================================*/

        test4.login();

        test4.like_a_post(user_accounts,"test2",2);
        test4.like_a_post(user_accounts,"test2",3);
        test4.like_a_post(user_accounts,"test2",4);
        test4.like_a_post(user_accounts,"test2",5);
        test4.like_a_post(user_accounts,"test2",6);
        test4.like_a_post(user_accounts,"test0",0);
        test4.add_comment_post(user_accounts,0,"comment");
        test4.follow_someone(user_accounts,"test1");
        test4.follow_someone(user_accounts,"test2");
        test4.follow_someone(user_accounts,"test3");
        test4.follow_someone(user_accounts,"test5");
        test4.follow_someone(user_accounts,"test6");
        test4.follow_someone(user_accounts,"test7");
        test4.follow_someone(user_accounts,"test8");
        test4.follow_someone(user_accounts,"test9");
        test4.unfollow_someone(user_accounts,"test1");
        test4.unfollow_someone(user_accounts,"test2");
        test4.create_new_post("test4 user post test0",10);
        test4.show_history();

        test4.logout();

     /*=========================================================================*/

        test5.login();

        test5.follow_someone(user_accounts,"test1");
        test5.follow_someone(user_accounts,"test3");
        test5.follow_someone(user_accounts,"test5");
        test5.follow_someone(user_accounts,"test7");
        test5.unfollow_someone(user_accounts,"test3");
        test5.like_a_post(user_accounts,"test2",3);
        test5.like_a_post(user_accounts,"test2",5);
        test5.like_a_post(user_accounts,"test2",4);
        test5.unlike_a_post(user_accounts,"test2",3);
        test5.add_comment_post(user_accounts,0,"comment test5");
        test5.add_comment_post(user_accounts,3,"comment test5");
        test5.add_comment_post(user_accounts,4,"comment test5");
        test5.uncomment_post(user_accounts,"test0",0);
        test5.show_history();

        test5.logout();
     /*=========================================================================*/

        test1.login();
        test1.unblock_someone(user_accounts,"test5");
        test1.logout();

        test0.login();
        test0.unblock_someone(user_accounts,"test5");
        test0.logout();

        test5.login();
        test5.add_comment_post(user_accounts,0,"comment test5");
        test5.follow_someone(user_accounts,"test0");
        test5.follow_someone(user_accounts,"test1");
        test5.uncomment_post(user_accounts,"test0",0);
        test5.show_history();
        test5.logout();

     /*=========================================================================*/

        test6.login();
        test6.add_comment_post(user_accounts,3,"comment test6");
        test6.like_a_post(user_accounts,"test4",10);
        test6.like_a_post(user_accounts,"test2",4);
        test6.follow_someone(user_accounts,"test4");
        test6.show_history();
        test6.logout();

     /*=========================================================================*/

        test7.login();

        test7.add_comment_post(user_accounts,3,"commment test 7");
        test7.like_a_post(user_accounts,"test4",10);
        test7.like_a_post(user_accounts,"test2",4);
        test7.follow_someone(user_accounts,"test2");
        test7.follow_someone(user_accounts,"test5");
        test7.follow_someone(user_accounts,"test6");
        test7.follow_someone(user_accounts,"test9");
        test7.unfollow_someone(user_accounts,"test5");
        test7.unfollow_someone(user_accounts,"test9");
        test7.add_comment_post(user_accounts,3,"comment test7");
        test7.add_comment_post(user_accounts,3,"comment test7");
        test7.add_comment_post(user_accounts,4,"comment test7");
        test7.add_comment_post(user_accounts,0,"comment test7");
        test7.uncomment_post(user_accounts,"test0",0);
        test7.unlike_a_post(user_accounts,"test2",4);
        test7.show_history();

        test7.logout();

     /*=========================================================================*/

        test8.login();

        test8.create_new_post("test8 post.",11);
        test8.block_someone(user_accounts,"test0");
        test8.block_someone(user_accounts,"test1");
        test8.block_someone(user_accounts,"test2");
        test8.block_someone(user_accounts,"test3");
        test8.block_someone(user_accounts,"test4");
        test8.block_someone(user_accounts,"test5");
        test8.block_someone(user_accounts,"test6");
        test8.block_someone(user_accounts,"test7");
        test8.block_someone(user_accounts,"test8");
        test8.block_someone(user_accounts,"test9");
        test8.unblock_someone(user_accounts,"test9");
        test8.show_history();
        test8.logout();

     /*=========================================================================*/
        
        test9.login();

        test9.add_comment_post(user_accounts,11,"comment test9");
        test9.show_history();

        test9.logout();
     /*=========================================================================*/
        test1.login();

        test1.add_comment_post(user_accounts,11,"comment test 1");
        test1.show_history();

        test1.logout();

     /*=========================================================================*/
        
        test1.login();

        

        test1.get_all_interactions(user_accounts,"test0");
        test1.get_all_interactions(user_accounts,"test1");
        test1.get_all_interactions(user_accounts,"test2");
        test1.get_all_interactions(user_accounts,"test3");
        test1.get_all_interactions(user_accounts,"test4");
        test1.get_all_interactions(user_accounts,"test5");
        test1.get_all_interactions(user_accounts,"test6");
        test1.get_all_interactions(user_accounts,"test7");
        test1.get_all_interactions(user_accounts,"test8");
        test1.get_all_interactions(user_accounts,"test9");

        test1.logout();

     /*=========================================================================*/


         long endtime = System.currentTimeMillis();
        float result = (endtime-startTime);
        result /=  10000.0f;
        System.out.println("running times -> " + (result));
    }
}
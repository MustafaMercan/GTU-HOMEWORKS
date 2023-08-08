public class main{
    public static void main(String [] args)
    {


        // TEST 1 
        user user_1 = new user("sibelgulmez");
        password1 password_1 = new password1("sibelgulmez","[rac()ecar]");
        password2 password2_1 = new password2(74);
        checkTest check_values_1 = new checkTest(user_1,password_1,password2_1);
        check_values_1.check_values(new int[]{4,17,29});

        // TEST 2 
        user user_2 = new user("");
        password1 password_2 = new password1("","[rac()ecar]");
        password2 password2_2 = new password2(74);
        checkTest check_values_2 = new checkTest(user_2,password_2,password2_2);
        check_values_2.check_values(new int[]{4,27,29});

        // TEST 3 
        user user_3 = new user("sibel1");
        password1 password_3 = new password1("sibel1","[rac()ecar]");
        password2 password2_3 = new password2(74);
        checkTest check_values_3 = new checkTest(user_3,password_3,password2_3);
        check_values_3.check_values(new int[]{4,27,29});

        //TEST 4 
        user user_4 = new user("sibel");
        password1 password_4 = new password1("sibel","pass[]");
        password2 password2_4 = new password2(74);
        checkTest check_values_4 = new checkTest(user_4,password_4,password2_4);
        check_values_4.check_values(new int[]{4,27,29});

        //TEST 5 
        user user_5 = new user("sibel");
        password1 password_5 = new password1("sibel","abcdabcd");
        password2 password2_5 = new password2(74);
        checkTest check_values_5 = new checkTest(user_5,password_5,password2_5);
        check_values_5.check_values(new int[]{5,27,29});
        
        //TEST 6 
        user user_6 = new user("sibel");
        password1 password_6 = new password1("sibel","[[[[]]]]");
        password2 password2_6 = new password2(32);
        checkTest check_values_6 = new checkTest(user_6,password_6,password2_6);
        check_values_6.check_values(new int[]{3,7,32});

        // TEST 7 
        user user_7 = new user("sibel");
        password1 password_7 = new password1("sibel","[no](no)");
        password2 password2_7 = new password2(33);
        checkTest check_values_7 = new checkTest(user_7,password_7,password2_7);
        check_values_7.check_values(new int[]{3,7,32});

        // TEST 8 
        user user_8 = new user("test");
        password1 password_8 = new password1("sibel","[rac()ecar]]");
        password2 password2_8 = new password2(79);
        checkTest check_values_8 = new checkTest(user_8,password_8,password2_8);
        check_values_8.check_values(new int[]{3,7,32});

        // TEST 9 
        user user_9 = new user("test");
        password1 password_9 = new password1("sibel","[rac()ecars]");
        password2 password2_9 = new password2(78);
        checkTest check_values_9 = new checkTest(user_9,password_9,password2_9);
        check_values_9.check_values(new int[]{3,7,32});

        // TEST 10 
        user user_10 = new user("test");
        password1 password_10 = new password1("sibel","[rac()ecar]");
        password2 password2_10 = new password2(5);
        checkTest check_values_10 = new checkTest(user_10,password_10,password2_10);
        check_values_10.check_values(new int[]{3,7,32});


        // TEST 11
        user user_11 = new user("test");
        password1 password_11 = new password1("sibel","[rac()ecar]");
        password2 password2_11 = new password2(35);
        checkTest check_values_11 = new checkTest(user_11,password_11,password2_11);
        check_values_11.check_values(new int[]{3,7,32});
    }
}
/**
 * This class is used to perform the necessary tests for the given inputs.
 */
public class checkTest{
    public user user_1;
    public password1 password_1;
    public password2 password2_1;

    /**
     * @param user_1 The user object to be tested.
     * @param password_1 The password1 object to be tested.
     * @param password2_1 The password2 object to be tested.
     */
    public checkTest(user user_1,password1 password_1, password2 password2_1){
        this.user_1 = user_1;
        this.password_1 = password_1;
        this.password2_1 = password2_1;
    }
    /**
     * Used for performing the necessary tests.
     * @param denominations To implement the required method in Part5, it takes an integer array named 'denominations' as input.
     */
    public void check_values(int [] denominations)
    {
        if(user_1.checkUserName() == true)
        {
            if(password_1.checkPassword1() == true)
            {
                if(password_1.containsUserNameSpirit() == true)
                {
                    if(password_1.isBalancedPassword() == true)
                    {
                        if(password_1.isPalindromePossible() == true)
                        {
                            if(password2_1.checkPassword2()== true)
                            {
                                if(password2_1.isExactDivision(denominations) == true)
                                {
                                    System.out.println("“The username and passwords are valid. The door is opening, please wait...”");
                                }
                            }
                       }
                    }
                }
            }
        }
    }
}
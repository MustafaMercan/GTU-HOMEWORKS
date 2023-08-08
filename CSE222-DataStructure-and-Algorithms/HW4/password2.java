/**
 * This class stores an integer password belonging to the user. It also includes the method for part 5 of the assignment.
 */
public class password2{
    int password;
    
    public password2(int password)
    {
        this.password = password;
    }
    public boolean checkPassword2()
    {
        if(this.password < 10 || this.password >10000)
        {
            System.out.println("The integer password is invalid due to It should be between 10 and 10,000.");
            return false;
        }

        return true;
    }
    /**
     * This method is the answer to the requested part5 of the assignment.If the number can be partitioned into exact parts, it returns true. If it cannot be partitioned, it returns false and prints an error message.
     * @param denominations This parameter is an integer array that is needed to test which numbers can be used to obtain the user's password.
     */
    public boolean isExactDivision(int[] denominations)
    {
        if(!isExactDivision(this.password,denominations,0,0))
        {
            System.out.println("The integer password is invalid due to It is not compatible with the denominations.Try again...");
            return false;
        }
        else
        {
            return true;
        }
    }
    /**
     * This method is the answer to the requested part5 of the assignment.If the number can be partitioned into exact parts, it returns true. If it cannot be partitioned, it returns false.
     * 
     * @param num holds the value of password2 belonging to the user.
     * @param denominations this parameter is an integer array that is needed to test which numbers can be used to obtain the user's password.
     * @param idx This parameter keeps track of the index we are currently on inside the 'denominations' array.
     * @param remaining This value allows us to check whether our recursive function has finished or not. The initial value starts as 0 and is incremented by the denominations[idx] value each time, then passed to the next function recursively. If the final value is equal to password, true is returned, otherwise false is returned.
     */
    public boolean isExactDivision(int num, int[] denominations, int idx, int remaining)
    {
        if(remaining == num)
            return true;
        if(idx == denominations.length)
            return false;
        int denomination = denominations[idx];
        while(remaining <= num)
        {
            if(isExactDivision(num,denominations,idx+1,remaining))
                return true;
            remaining += denomination;
        }
        
        return isExactDivision(num, denominations, idx + 1, remaining - denomination);
    }
}
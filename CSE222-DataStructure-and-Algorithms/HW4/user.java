/**
 * This class stores the username received from the user as a string and has a method that checks whether this username complies with the rules.
 */
public class user{
    char [] userName;
    public user(String userName){
        this.userName = userName.toCharArray();
    }
    /**
     * This method tests whether the username complies with the rules stated in the PDF. If it complies, it returns true, otherwise it returns false.
     */
    public boolean checkIfValidUsername()
    {
        if(userName.length == 0)
            return false;
        return checkIfValidUsername(0);
    }
    /**
     * This recursive method tests whether the username complies with the rules stated in the PDF. If it complies, it returns true, otherwise it returns false.
     * @param currentIndex This parameter holds the index value of our current position in the char array.
     */
    public boolean checkIfValidUsername(int currentIndex)
    {
        if(currentIndex == userName.length)
            return true;
        if((userName[currentIndex] >= 'a' && userName[currentIndex] <= 'z') || (userName[currentIndex] >= 'A' && userName[currentIndex] <= 'Z'))
        {
            return checkIfValidUsername(currentIndex + 1);
        }
        return false;
    }

    /**
     * This method, in the same way, prints a message to the screen depending on whether the username is valid or not, and returns true or false depending on its validity.
     */
    public boolean checkUserName()
    {

        if(this.userName.length == 0)
        {
            System.out.println("The username is in valid due to It should have at least 1 character. Try again...");
            return false;
        }
        if(!this.checkIfValidUsername())
        {
            System.out.println("The username is invalid due to It should have letters only. Try again... ");
            return false;
        }
        return true;
    }


}
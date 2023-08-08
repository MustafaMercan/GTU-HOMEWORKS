import java.util.Stack;

/**
 * This class stores a string username and a string password belonging to the user. It contains methods for part2, part3, and part4 as requested in the PDF.
 */
public class password1{

    public String userName;
    public String password1;
    public password1(String userName, String password)
    {
        this.userName = userName;
        this.password1 = password;
    }

    /**
     * This method enables the implementation of part2 as requested in the PDF. If there is at least one identical character between Username and Password, it returns true, otherwise it returns false and prints an error message.
     */
    public boolean containsUserNameSpirit()//part2
    {
        Stack <Character> stackPassword = new Stack<Character>();
        Stack <Character> stackUsername = new Stack<Character>();

        for(char element : this.password1.toCharArray())
        {
            if(Character.isLetter(element))
                stackPassword.push(element);
        }

        for(char element : this.userName.toCharArray())
        {
            if(Character.isLetter(element))
                stackUsername.push(element);
                
        }
        while(!stackPassword.isEmpty())
        {
            char c = stackPassword.pop();
            if(stackUsername.search(c) != -1)
               return true; 
        }

        System.out.println("The string password is invalid due to It should have at least 1 character from the username. Try again...");
        return false;
    }

    /**
     * This method enables the implementation of part3 as requested in the PDF. It checks whether any opened parentheses are closed. If they are closed, it returns true; if they are not closed, it returns false and prints an error message.
     */
    public boolean isBalancedPassword()//part3
    {
        Stack <Character> passwordStack = new Stack <Character>();
        Stack <Character> stack = new Stack <Character>();
        char top;
        
        for(char element : this.password1.toCharArray())
        {
            if(checkBracket(element))
                passwordStack.push(element);
        }
        while(!passwordStack.isEmpty())
        {
            char ch = passwordStack.peek();
            if(ch ==')' || ch == '}' || ch == ']')
            {
                
                stack.push(ch);
            }
            else if(ch == '(' || ch == '{' || ch == '[')
            {
                if(stack.isEmpty())
                {
                    System.out.println("The string password is invalid due to It should be balanced. Try again...");
                    return false;
                }
                else
                {
                    
                    if(!check_match_bracket(stack.peek(),passwordStack.peek()))
                    {
                        System.out.println("The string password is invalid due to It should be balanced. Try again...");
                        return false;
                    }
                    stack.pop();
                }
            }
            top = passwordStack.pop();
        }
        if(passwordStack.isEmpty() && stack.isEmpty())
            return true;
        
        System.out.println("The string password is invalid due to It should be balanced. Try again...");
        return false;


    }
    /**
     * This method checks whether the parameter sent is equal to any parenthesis character. If it is equal, it returns true; otherwise, it returns false.
     * @param ch This parameter holds the char variable that we want to compare.
     */
    public boolean checkBracket(char ch)
    {
        if(ch == '(' || ch == '{' || ch == '[' || ch == ')' || ch == '}' || ch == ']')
            return true;
        return false;
    }
    /**
     * This method checks whether the closed version of an open parenthesis exists. If it exists, it returns true; otherwise, it returns false
     * @param last_bracket This parameter holds the value of the closed parenthesis.
     * @param first_bracket This parameter holds the value of the open parenthesis.
     */
    public boolean check_match_bracket(char last_bracket,char first_bracket)
    {
        if((last_bracket == ')' && first_bracket == '(') || (last_bracket == ']' && first_bracket == '[') || (last_bracket == '}' && first_bracket == '{'))
        {
            return true;
        }
        return false;
    }
    /**
     * This method performs part4 as requested in the PDF. If a palindrome value can be obtained from the characters in Password1, it returns true; otherwise, it returns false. However, while performing this operation, it ignores the parentheses in Password1
     */
    public boolean isPalindromePossible()//part4
    {
        char [] charArr = removeBraces(this.password1.toCharArray());
        
        
        if(charArr == null)
            return false;

        if(isPalindromePossible(charArr,0) == false)
        {
            System.out.println("The string password is invalid due to It should be possible to obtain a palindrome from the string password.Try again...");
            return false;
        }
        else
            return true;

    }
    /**
     * This method serves the same purpose as the other method, but allows us to use it recursively.
     * @param arr This parameter holds the values of Password1
     * @param idx This value holds the index information of where we are in the Password array
     */
    public boolean isPalindromePossible(char[] arr,int idx)
    {
        int idxOtherLetter;
        if((arr.length == 0 || arr.length == 1))
            return true;
        else if(idx < arr.length)
        {
            idxOtherLetter = check_letter(arr,idx);
            if(idxOtherLetter != -1 && idxOtherLetter < arr.length)
            {
                arr = removeElement(arr,idx,idxOtherLetter);
                return isPalindromePossible(arr,idx);
            }
            if(idx + 1 < arr.length)
            {
                return isPalindromePossible(arr,idx+1);
            }
        }
        return false;
    }

    /**
     * This method is a helper method. It checks if there is a character in the sent char array that matches the character at the sent index. If there is, it returns the index of that character. If not, it returns -1
     * @param arr Stores the char array to be operated on
     * @param idx Holds the current index value of the element we are looking for in the array.
     */
    public int check_letter(char[] arr, int idx)
    {
        for(int i = 0 ; i < arr.length ; i++)
        {
            if((i != idx) && (arr[idx] == arr[i]))
                return i;
        }
        return -1;
    }


    /**
     * This method transfers the elements of a given char array to a new one without the values at two specified indices, and then returns the new char array.
     * @param arr The array to be processed.
     * @param index The index value of the element to be deleted.
     * @param index2 The index value of the element to be deleted.
     */
    public char [] removeElement(char[] arr, int index,int index2)
    {
        if(arr == null || index < 0 || index >= arr.length)
            return arr;
        char[] result = new char[arr.length - 2];
        for(int i = 0, j = 0; i < arr.length; i++)
        {
            if(i!=index && index2 != i)
            {
                result[j++] = arr[i];
            }
        }
        return result;
    }
    /**
     * This method is used to clear the empty space in memory if the number of elements in the array is smaller than the size of the array.
     * @param arr The array to be copied.
     * @param newLength New size of the array to be transferred to.
     */
    public static char[] copyOf(char[] arr, int newLength)
    {
        char[] newArr = new char[newLength];
        for (int i = 0; i < Math.min(arr.length, newLength); i++) 
        {
            newArr[i] = arr[i];
        }
        return newArr;
    }

    /**
     * This method removes all parentheses in the array.
     * @param arr The array on which the operation will be performed.
     */
    public char [] removeBraces(char[] arr)
    {
        char [] result = new char[arr.length];
        int idx = 0;
        for(int i = 0 ; i < arr.length ; i++)
        {
            if(arr[i] == '{' || arr[i] == '[' || arr[i] == '(' ||arr[i] == '}' ||arr[i] == ']' ||arr[i] == ')')
                continue;
            result[idx++] = arr[i];
        }
        return copyOf(result,idx);
    }
    /**
     * This function performs the necessary checks related to password1. If there is any violation of the rules, it returns false and displays an error message. If not, it returns true.
     */

    public boolean checkPassword1()
    {
        boolean flag_1 = false;
        boolean flag_2 = true;
        int count = 0;
        char [] password = this.password1.toCharArray();

        if(password.length < 8)
        {
            System.out.println("The string password is invalid due to It should have at least 8 characters.Try again...");
            return false;
        }

        for(int i = 0 ; i < password.length ; i++)
        {
            if(checkBracket(password[i]))
                count++;
            else if(Character.isLetter(password[i]))
                flag_1 = true;
        }
        if(count < 2)
        {
            System.out.println("The string password is invalid due to It should have at least 2 brackets.Try again...");
            return false;
        }
        
        if(flag_1 == false)
        {
            System.out.println("The string password is invalid due to It should have letters too.Try again...");
            return false;
        }
        return true;
    }
}
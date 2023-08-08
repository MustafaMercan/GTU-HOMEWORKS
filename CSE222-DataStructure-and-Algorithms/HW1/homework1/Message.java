package homework1;
public class Message extends Account{
    private long message_id;
    private long sender_id;
    private long receiver_id;
    private String content;


    /**
     * This constructor method allows us to assign the parameters that are received when we first create our object to the variables inside our object.
     * @param message_id is message ID belonging to the message.
     * @param sender_id is Account ID belonging to the sender.
     * @param receiver_id is Account ID belonging to the receiver.
     * @param content is the content of the message.
     * @param user_name is username beloning to the user.
     */
    public Message(long message_id,long sender_id, long receiver_id, String content,String user_name)
    {
        super((int)receiver_id,user_name);
        this.message_id = message_id;
        this.sender_id = sender_id;
        this.receiver_id = receiver_id;
        this.content = content;
    }
    /**
     * It prints the information related to this message.
     */
    public void print_informations()
    {
        System.out.println("MESSAGE ID: " + this.message_id);
        System.out.println("Content: " + this.content);
    }
    /**
     * It returns the receiver ID.
     */
    public long get_receiver_id(){return this.receiver_id;}
    /**
     * It returns the message ID.
     */
    public long get_message_id(){return this.message_id;}
    /**
     * It returns the message's content.
     */
    public String get_message_content(){return this.content;}
}
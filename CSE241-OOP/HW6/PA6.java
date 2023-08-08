public class PA6 {
    public static void main(String[] args)
    {
        entry check = new entry();
        player p1 = new player();//hold video,image;
        player p2 = new player();
        viewer v1 = new viewer();
        viewer v2 = new viewer();

        check.register(p1);
        check.register(p2);
        check.register(v1);
        check.register(v2);

	System.out.print("if the list is empty, the empty list is printed and then returned as null\n");
        playable po = (playable)p1.currently_playing();
        non_playable np = (non_playable)v1.currently_viewer();


        System.out.print("\n\n\n");
        System.out.print("if list is empty the current_playing and current_viewer functions return null\n");
        if(po ==null)
        {
            System.out.print("The player list is empty\n");
        }
        if(np==null)
        {
            System.out.print("The viewer list is empty\n");
        }
        System.out.print("\n\n\n");
        

        check.add(new video("video_name_1","duration_information","other_information"));
        check.add(new image("image_name_1","dimension_information","other_information"));
        check.add(new audio("audio_name_1","duration_information","other_information"));
        check.add(new text("text_name_1","other_infrmation"));

        System.out.print("p1.show() function outputs \n");
        p1.show_list();
        System.out.print("\np2.show() function outputs \n");
        p2.show_list();
        System.out.print("\nv1.show() function outputs \n");
        v1.show_list();
        System.out.print("\nv2.show() function outputs \n");
        v2.show_list();
        System.out.print("\nfirst element's information\n");
        
        System.out.print("for p1:\n");
        po =(playable) p1.currently_playing();
        po.info();
        System.out.print("for p2:\n");
        po = (playable)p2.currently_playing();
        po.info();
        np = (non_playable) v1.currently_viewer();
        System.out.print("for v1:\n");
        np.info();
        System.out.print("for v2:\n");
        np = (non_playable) v2.currently_viewer();
        np.info();
        System.out.print("\n\n\n");
        System.out.print("Remove for po\nBefore:\n");
        System.out.print("p1:\n");
        p1.show_list();
        System.out.print("p2:\n");
        p2.show_list();
        check.remove(po);
        System.out.print("After\n");
        System.out.print("p1:\n");
        p1.show_list();
        System.out.print("p2:\n");
        p2.show_list();

        System.out.print("\n\n\n");

        System.out.print("Remove for np\nBefore:\n");
        System.out.print("v1:\n");
        v1.show_list();
        System.out.print("v2:\n");
        v2.show_list();

        check.remove(np);

        System.out.print("After:\n");
        System.out.print("v1:\n");
        v1.show_list();
        System.out.print("v2:\n");
        v2.show_list();

        System.out.print("\n\n\n");

        

        //adds some element 


        check.add(new video("video_name_2","duration_information","other_information"));
        check.add(new image("image_name_2","dimension_information","other_information"));
        check.add(new audio("audio_name_2","duration_information","other_information"));
        check.add(new text("text_name_2","other_information"));

        check.add(new video("video_name_3","duration_information","other_information"));
        check.add(new image("image_name_3","dimension_information","other_information"));
        check.add(new audio("audio_name_3","duration_information","other_information"));
        check.add(new text("text_name_3","other_information"));

        System.out.print("current state after adding a few elements:\n");
        System.out.print("p1:\n");
        p1.show_list();
        System.out.print("p2:\n");
        p2.show_list();
        System.out.print("v1:\n");
        v1.show_list();
        System.out.print("v2:\n");
        v2.show_list();

        System.out.print("\n\n\n");
        po = (playable)p1.currently_playing();
        np = (non_playable)v1.currently_viewer();

        System.out.print("current elements : \n");
        System.out.print("for po:\n");
        po.info();
        System.out.print("for np:\n");
        np.info();
        System.out.print("\n\n\n");
        System.out.print("next function with image  for v1:\n");
        v1.next("image");
        np = (non_playable)v1.currently_viewer();
        np.info();
        System.out.print("next function with video for p1 :\n");
        p1.next("video");
        po = (playable)p1.currently_playing();
        po.info();
        System.out.print("\n\n\n");

        System.out.print("previous function with text for v1:\n");
        v1.previous("text");
        np = (non_playable)v1.currently_viewer();
        np.info();

        System.out.print("previous function with audio for p1:\n");
        p1.previous("audio");
        po = (playable)p1.currently_playing();
        po.info();

        System.out.print("\n\n\n");
        p1.show_list();
        System.out.print("If current element is removed from the list, it moves to the next element\n");
        System.out.print("Current element : \n");
        po.info();
        System.out.print("current element after element is removed:\n");
        check.remove(po);
        po = (playable)p1.currently_playing();
        po.info();
        System.out.print("\n\n\n");
        System.out.print("If the next type is not found to the end of the list, the list returns to the top and a notification message is written.\n");
        p1.next("video");
        p1.next("video");
        po = (playable)p1.currently_playing();
        po.info();
        System.out.print("\n\n\n");
        System.out.print("If the previous type is not found to the end of the list, the list returns to the top and a notification message is written.\n");
        v1.next("text");
        v1.previous("text");
        v1.previous("text");
        np = (non_playable)v1.currently_viewer();
        np.info();
        

        


    }
    
}

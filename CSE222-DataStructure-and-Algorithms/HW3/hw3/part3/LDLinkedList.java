package part3;
import java.util.AbstractList;
import java.util.List;


public class LDLinkedList<E> extends AbstractList<E> implements List<E> {
    
    private Node <E> head;
    private int size;

    private static class Node <E> {
        private E data;
        private Node<E> next;
        private boolean isDeleted;
        
        public Node(E data) 
        {
            this.data = data;
            this.next = null;
            this.isDeleted = false;
        }
    }
    
    public LDLinkedList() 
    {
        this.head = null;
        this.size = 0;
    }

    
    public int size() {
        return size;
    }
    
    public boolean add(E element) 
    {
         Node<E> newNode = new Node<>(element);
        if (head == null) 
        {
            head = newNode;
        } 
        else 
        {
            Node <E> currentNode = head;
            while (currentNode.next != null) 
            {
                currentNode = currentNode.next;
            }
            currentNode.next = newNode;
        }
        size++;
        return true;
    }
    
    public E get(int index) 
    {

        if (index < 0 || index >= size) 
        {
            throw new IndexOutOfBoundsException("Index out of range.");
        }
        int currentIndex = 0;
        Node <E> currentNode = head;
        while (currentNode != null) 
        {
            if (!currentNode.isDeleted) 
            {
                if (currentIndex == index) 
                {
                    return currentNode.data;
                }
                currentIndex++;
            }
            currentNode = currentNode.next;
        }
        throw new IndexOutOfBoundsException("Index out of range.");
    }

    
    public E remove(int index) 
    {
        if (index < 0 || index >= size)
        {
            throw new IndexOutOfBoundsException("Index out of range.");
        }

        Node <E> currentNode = head;
        int currentIndex = 0;
        while (currentNode != null) 
        {
            if (!currentNode.isDeleted) 
            {
                if (currentIndex == index) 
                {
                    currentNode.isDeleted = true;
                    size--;

                    if(count_deleted() == 2)
                        physicalDelete(); 
                    return currentNode.data; 
                }
                currentIndex++;
            }
            currentNode = currentNode.next;
        }
        return null;
    }

    public void physicalDelete() 
    {
        Node <E> currentNode = head;
        Node <E> previousNode = null;
        while (currentNode != null) 
        {
            if (currentNode.isDeleted) {
                if (previousNode == null) 
                {
                    head = currentNode.next;
                } 
                else 
                {
                    previousNode.next = currentNode.next;
                }
            } 
            else 
            {
                previousNode = currentNode;
            }
            currentNode = currentNode.next;
        }
    }

    public int count_deleted()
    {
        Node<E> currentNode = head;
        int count = 0; 
        

        while(currentNode != null)
        {
            if(currentNode.isDeleted)
                count++;
            currentNode = currentNode.next;
        }
        return count;
    }
}

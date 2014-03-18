//This is my LinkedList class from programming project 1.  Only change is I made the top node public since that's the easist way to grab it in base blocks.
#ifndef LINKEDLIST_INCLUDED
#define LINKEDLIST_INCLUDED
#include <iostream>
template <typename T>
class LinkedList {
    struct Node {
        T content;
        Node* next;
    };
    private:
        int length;
    public:
        Node* first;
    
        LinkedList(){
            first = 0;
            length = 0;
        }//end constructor

        ~LinkedList(){
            //Nodes are on the heap, so delete them all.  N time.
            Node* temp = first;
            while (first){
                temp = (*first).next;
                delete first;
                first = temp;
            }//end while
        }//end deconstructor

        void add(T a){
        //append to the TOP of the list.  Constant time instead of N time.  May throw off expectations, but for this project early/late additions being first is irrelevant
            Node* pTemp = new Node;
            (*pTemp).next = first;
            (*pTemp).content = a;
            first = pTemp;
            length++;
        }//end add

        T operator[](int i){
        //Return the ith element.  N time.
            if (i < length){
                Node* temp = first;
                while(i){
                    i--;
                    temp = (*temp).next;
                }//end while
                return (*temp).content;
            }//end if
            else {
                std::cout << "Index out of bounds" << std::endl;
                return T();
            }//end else
        }//end get

        bool contains(T a){
        //Return true if any of the nodes holds a as its content.  N time.
            Node* temp = first;
            while (temp){
                if ((*temp).content == a) return true;
                temp = (*temp).next;
            }//end while
            return false;
        }//end contains

        int getLength(){
            return length;
        }//end length

        void remove(int i){
            //remove the ith element.
            if (i < length){
                Node* theNode = first;
                Node* nodesParent = 0;
                while (i){
                    nodesParent = theNode;
                    theNode = (*theNode).next;
                    i--;
                }//end while
                //Set the parent's next to the node's next.  If we're at the top, move the top.  Then delete the node.
                if (nodesParent) (*nodesParent).next = (*theNode).next;
                else first = (*theNode).next;
                delete theNode;
                length--;
            } else std::cout << "Index out of bounds" << std::endl;
        }//end remove
};
#endif

#ifndef LINKEDLIST_INCLUDED
#define LINKEDLIST_INCLUDED
template <typename T>
class LinkedList{
    struct Node {
        Node* next;
        T content;
    };
    private:
        Node* top;
        int length;

        Node& last(){
            //Assume being called in a non-empty scenerio
            //if (!top) return Node;

            Node* temp = top;
            while (temp->next) temp = temp->next;
            return *temp;
        }//end last
    public:
        LinkedList(){
            top = 0;
            length = 0;
        }//end constructor
        ~LinkedList(){
            Node* temp;
            while (top){
                temp = top->next;
                delete top;
                top = temp;
            }//end while
        }//end deconstructor

        int getLength(){
            return length;
        }//end getLength

        void add(T a){
            length++;
            Node* newNode = new Node;
            newNode->next = 0;
            newNode->content = a;

            if (!top) top = newNode;
            else last().next = newNode;
        }//end add

        bool contains(T a){
            Node* temp = top;
            while (temp){
                if (temp->content == a) return true;
                temp = temp->next;
            } return false;
        }//end contains

        T operator[](int i){
            if (i >= length) return T();
            Node* temp = top;
            while (i){
                i--;
                temp = temp->next;
            }//end while
            return temp->content;
        }//end get
};
#endif

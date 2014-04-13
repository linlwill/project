#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED
class NotInQueueException {
    public:
        NotInQueueException(){}
};
template <typename T>
class Queue {
    public:
        struct Node {
            T content;
            Node* front;
            Node* rear;
        };//end node

        Node* first;
        Node* last;

        Queue(){
            first = 0;
            last = 0;
        }//end initializer

        ~Queue(){
            while(first){
                Node* temp = first->rear;
                delete first;
                first = temp;
            }//end while
        }//end deconstructor

        bool notEmpty(){
            return first;
        }//end notEmpty

        void push(T thing){
            //New node.  Its front is the last.  It is the last.  If nothing in front it is the front.
            Node* temp = new Node;
            temp->content = thing;
            temp->front = last;
            temp->rear = 0;
            if (last) last->rear = temp;
            else first = temp;
            last = temp;
        }//end push

        T pull(){
            //If empty, error.  First's rear is now front.  If that emptied the list, last is 0.
            if (!first) throw NotInQueueException();
            T temp = first->content;
            Node* newFirst = first->rear;
            delete first;
            first = newFirst;
            if (first) first->front = 0;
            else last = 0;
            return temp;
        }//end pull

};//end class
#endif

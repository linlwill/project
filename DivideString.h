#ifndef SLICEASTRING_INCLUDED
#define SLICEASTRING_INCLUDED
#include <string>
#include "LinkedList.h"
//Divide a string up by a demarkation char. Return a linked list full of those blocks.

LinkedList<std::string> divideString(std::string input, char demark, bool continuous = true){
    LinkedList<std::string> list = LinkedList<std::string>();
    std::string buffer = "";
    for (int i = 0; i < input.length(); i++){
        if (input[i] == demark){
            //Doing continuous, strings of demarks count as one.  Turn cont off, and Hello!!World demarked with '!' will make a list {"Hello","","World"}
            if (buffer.length() || !continuous){
                list.add(buffer);
                buffer = "";
            }//end if
        }//end if-demark
        else {
            buffer += input[i];
        }//end else - aka not demark
    }//end for
    list.add(buffer);
    return list;
}//end divide

#endif

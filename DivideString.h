#ifndef SLICEASTRING_INCLUDED
#define SLICEASTRING_INCLUDED
#include <string>
#include "LinkedList.h"
//Divide a string up by a demarkation char. Return a linked list full of those blocks.

LinkedList<std::string> divideString(std::string input, char demark){
    LinkedList<std::string> list = LinkedList<std::string>();
    std::string buffer = "";
    for (int i = 0; i < input.length(); i++){
        if (input[i] == demark){
            //Forget continuity.  Do it later.  Dump temp into the list and reset.
            if (buffer.length()){
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

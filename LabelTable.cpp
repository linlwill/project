//This is a data structure that holds labels and their corresponding addresses.
//When a label is found, it can be added to this along with the address it was found at.
//Later, a label is used, it can be used as a key to return that value.
//It is implemented as a singly-linked list of Labels. Searching is O(N).
#ifndef LABELTABLE_INCLUDED
#define LABELTABLE_INCLUDED
#include <string>
using namespace std;

class LabelTable{
  struct Label {
    int address;
    string keyword;
    Label* next;
  };//end struct
  
  private:
    Label* first;
    int length;
  
  public:
    LabelTable();
    bool contains(string keyword);
    int operator[](string keyword);
    bool add(string keyword, int address);
    
};//end class

LabelTable::LabelTable(){
  //Initialize to zero.
  first = 0;
  length = 0;
}//end initializer

bool LabelTable::contains(string keyword){
  //Go through the list.  if Label.keyword == keyword, return true.  If the loop exits, return false
  Label* next = first;
  string nodeKey;
  for (int i = 0; i < length; i++){
    if ((*next).keyword == keyword) return true;
    next = (*next).next;
  }//end for
  return false;
}//end contains

bool LabelTable::add(string keyword, int address){
  //Search table for the keyword.  If exists, return false.  Else, create new node and add to top of list, return true.
  if (contains(keyword)) return false;
  else {
    Label* temp = new Label;
    (*temp).keyword = keyword;
    (*temp).address = address;
    (*temp).next = first;
    first = temp;
    length++;
    return true;
  }//end else
}//end add

int operator[](string keyword){
  //Search the list for a node with the keyword.  If found, return that address.  If not found, return -1 as a flag.
  Label* next = first;
  for (int i = 0; i < length; i++){
    if ((*next).keyword == keyword) return (*next).address;
    next = (*next).next;
  }//end for
  return -1;
}//end get
#endif

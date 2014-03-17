//This is a data structure that holds symbols and their corresponding values.
//When a symbol is found, it can be added to this along with the value it represents.
//Later, when a symbol is encountered, it can be used as a key to return that value.
//It is implemented as a singly-linked list of Symbols. Searching is O(N).
#ifndef SYMBOLTABLE_INCLUDED
#define SYMBOLTABLE_INCLUDED
#include <string>

class SymbolTable{
  struct Symbol {
    int value;
    std::string keyword;
    Symbol* next;
  };//end struct

  private:
    Symbol* first;

  public:
    SymbolTable();
    ~SymbolTable();
    bool contains(std::string keyword);
    int operator[](std::string keyword);
    bool add(std::string keyword, int address);

};//end class

SymbolTable::SymbolTable(){
  //Initialize to zero.
  first = 0;
}//end constructor

SymbolTable::~SymbolTable(){
  //Iterate through the nodes deleting them.
  Symbol* temp;
  while (first){
    temp = (*first).next;
    delete first;
    first = temp;
  }//end while
}//end deconstructor

bool SymbolTable::contains(std::string keyword){
  //Go through the list.  if Label.keyword == keyword, return true.  If the loop exits, return false
  Symbol* next = first;
  while(next){
    if ((*next).keyword == keyword) return true;
    next = (*next).next;
  }//end for
  return false;
}//end contains

bool SymbolTable::add(std::string keyword, int value){
  //Search table for the keyword.  If exists, return false.  Else, create new node and add to top of list, return true.
  if (contains(keyword)) return false;
  else {
    Symbol* temp = new Symbol;
    (*temp).keyword = keyword;
    (*temp).value = value;
    (*temp).next = first;
    first = temp;
    return true;
  }//end else
}//end add

int SymbolTable::operator[](std::string keyword){
  //Search the list for a node with the keyword.  If found, return that address.  If not found, return -1 as a flag.
  Symbol* next = first;
  while (next){
    if ((*next).keyword == keyword) return (*next).value;
    next = (*next).next;
  }//end for
  return -1;
}//end get
#endif

#ifndef DIRECTIVES_INCLUDED
#define DIRECTIVES_INCLUDED
#include <string>
#include <BinarySearchTree.h>

namespace directives {
//Keep a BST of all directive names.
BinarySearchTree<std::string> DB = BinarySearchTree<std::string>();
bool DBinitialized = false;
void initDB(){
  if (DBinitialized) return;
  directives::DBinitialized = true;
  DB.add("START");
  DB.add("END");
  DB.add("BYTE");
  DB.add("RESB");
  DB.add("WORD");
  DB.add("RESW");
  DB.add("BASE");
  DB.add("EQU");
}//end init

}//end namespace
#endif

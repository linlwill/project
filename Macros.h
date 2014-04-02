#ifndef MACROSINCLUDED
#define MACROSINCLUDED
#include "primary"
#include "LinkedList.h"

namespace macros {
  
class Macro{
  public:
    LinkedList<std::string> blocks;
    LinkedList<void*> defaultArgs;
    int argCount[2];
    Macro(){
        
    }
};
std::map<std::string,Macro> DB;
void initDB();
Macro get(std::string keyword);

}//end namespace
#endif

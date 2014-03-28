#ifndef DIRECTIVES_INCLUDED
#define DIRECTIVES_INCLUDED
#include <string>
#include <sstream>
#include <map>

namespace directives {
  //Keyword will map to an integer referring to 1+ how many arguments the directive takes.  1+ is necessary so 0 can be "does not include" instead of "no arguments"
  map<std::string,int> DB;
  void initDB();
  bool DBinitialized = false;
  int get(std::string keyword);
  void process(std::string opor, std::string* opands);


  void initDB(){
    if (DBinitialized) return;
    directives::DBinitialized = true;
    DB["BASE"] = 2;
    DB["EQU"] = 2;
  }//end init
  
  int get(std::string keyword){
    initDB();
    return DB[keyword];
  }//end get
  
  void process(std::string opor, std::string* opands){
    //Wish I could use switches with strings.  I like switches.
    if (opor == "BASE"){
      //Set the base to be the operand.  Or call empty to close any bases. 
      std::string opand = opands[1];
      //There is no harm in calling close even if there isn't one open.
      Base::endBlock(CURRENTADDRESS);
      if (opand != "") Base::startBlock(opand,CURRENTADDRESS);
    }//end base
    
    else if (opor == "EQU"){
      //Create a constant, with value label.  Convert string to int and set as map value.
      int value;
      std::stringstream(opands[1]) >> value;
      labelTable[opands[0]] = value;
    }//end equ
    
  }//end process

}//end namespace
#endif

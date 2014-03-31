#ifndef DIRECTIVES_INCLUDED
#define DIRECTIVES_INCLUDED
#include <string>
#include <math.h>
#include <map>

int toInt(std::string a){
    //For every digit, handle as a number using base-10
    int sum = 0;
    int neg = 0;
    if (a[0] == '-') neg = 1;
    for (int i = neg; i < a.length(); i++) sum += pow(10, a[i-neg] - '0');
    return sum * pow(-1,neg);
}//end toInt

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
      Base::endBlock(primary::CurrentAddress);
      if (opand != "") Base::startBlock(opand,primary::CurrentAddress);
    }//end base
    
    else if (opor == "EQU"){
      //Create a constant, with value label.  Convert string to int and set as map value.
      labelTable[opands[0]] = toInt(opands[1]);
    }//end equ
    
    else if (opor == "START"){
      //The operand is where to start the program, as an integer.  Later this function can be expanded to handle control sections/program blocks.
      int a = toInt(opands[1]);
      primary::CurrentAddress = a;
      primary::startingAddress = a;
    }//end start
    
  }//end process

}//end namespace
#endif

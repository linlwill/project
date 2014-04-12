#ifndef DIRECTIVES_INCLUDED
#define DIRECTIVES_INCLUDED
#include "primary.h"
#include "Modification.h"

namespace directives {
  //Keyword will map to an integer referring to 1+ how many arguments the directive takes.  1+ is necessary so 0 can be "does not include" instead of "no arguments"
  std::map<std::string,int> DB;
  void initDB();
  bool DBinitialized = false;
  int get(std::string keyword);
  void process(std::string opor, std::string* opands);


  void initDB(){
    if (DBinitialized) return;
    directives::DBinitialized = true;
    DB["BASE"] = 2;
    DB["EQU"] = 2;
    DB["START"] = 2;
    DB["END"] = 1;
  }//end init

  int get(std::string keyword){
    initDB();
    return DB[keyword];
  }//end get

  void process(std::string opor, std::string* opands){
    //Wish I could use switches with strings.  I like switches.
    if (opor == "BASE"){
      //Set the base to be the operand.  Or call empty to close any bases.
      //There is no harm in calling close even if there isn't one open.
      Base::endBlock(primary::CurrentAddress);
      int i;
      std::stringstream(opands[1]) >> i;
      if (opands[1] != "") Base::startBlock(i,primary::CurrentAddress);
    }//end base

    else if (opor == "EQU"){
      //Create a constant, with value label.  Convert string to int and set as map value.
      int i;
      std::stringstream(opands[1]) >> i;
      primary::labelTable[opands[0]] = i;
    }//end equ

    else if (opor == "START"){
      //The operand is where to start the program, as an integer.  Its label is the program's name, default "program".  Later this function can be expanded to handle control sections/program blocks.
      int a = primary::forceInt(opands[1]);
      if (opands[0] == "") primary::programName = "program";
      else primary::programName = opands[0];
      primary::CurrentAddress = a;
      primary::startingAddress = a;
    }//end start

    else if (opor == "END"){
        //Wherever we are, how much space we're using, that's where we end.
        primary::programLength = primary::CurrentAddress;
    }

  }//end process

}//end namespace
#endif

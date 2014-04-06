#include "primary.h"
namespace primary {
  
std::string opor;
std::string* args;

LinkedList<std::string> blockList;

class UnrecognizedLineException{
  public:
    std::string errorCode;
    UnrecognizedLineException(std::string a = ""){
      errorCode = a;
    }//end constructor
};//end exception

for (line in file){
  state = lineCase::passOne(line);
  label = state % 2;
  
  //Even states are the same as their odds, but they have labels.  Switches are the devil.
  state -= label;
  if (state == 1){
      //Increment current location by instruction mode + e of the line
      blockList = divideString(line,' ');
      opor = blockList[label];
      
      CurrentAddress += (instructions::get(opor).format + fb::e(line,false) );   
  }//end instruction
  else if (state == 3){
      //Directive.  Operator is first block, or second if label. Operands follow.  0 is always the label.
      blockList = divideString(line,' ');
      opor = blockList[label];
      
      //0 will be label, or empty.  1... will be arguments, the amount of which is dictated by the directive.  Get thus dictates how many things to grab, b/c the extra 1 that exists so 1 can be 0 and 0 can be n/a compensates for the label.  I love when stuff synergizes.
      argCount = directives::get(opor);
      args = new std::string[argCount];
      if (label) args[0] = blockList[0];
      //For nonzero arguments, go one by one through the directive's demanded operands.  It's possible to run out of blocks here, like BASE asking for one but allowing none, so use LinkedList's exception handling.
      try{
         for (int i = 1; i < argCount; i++) args[i] = blockCount[i];
      } catch(NotInListException){
         //Cricket sounds.  new[] initializes the spaces to "", so passing as-is preserves empties as flags.
      }//end exceptions
      directives::process(opor,args);
      delete[] args;
  }//end directive
  else if (state == 5){
      //Macro.  Start grabbing lines.
      //Not implemented yet!
  }


for (line in file){
  state = lineCase::passTwo(line);
  label = state % 2;
  state -= label;
  
  if (state == 1){
      continue;
  } else if (state == 3){
      block = objectCode(line,label);
  } else if (state == 5){
      //Not implemented
  } else throw UnrecognizedLineException(line);
  
}//end pass two

}//end namespace

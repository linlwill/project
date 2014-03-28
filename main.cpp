
namespace primary {
  
int ::CurrentAddress;
  
std::string* args;
std::string opor;
LinkedList<std::string> blockList;
int label, state, workingBlock, argCount;
Instruction theInst;

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
  
  //Even states are the same as their odds, but they have labels.  
  switch (state - label){
    case 1://Instruction.  Increment current location by instruction mode + e of the line
      blockList = divideString(line,' ');
      opor = blockList[label];
      
      theInst = instructions::get(opor);
      ::CurrentAddress += (theInst.format + fb::e(line,false) - '0');
    case 3://Directive.  Operator is first block, or second if label. Operands follow.  0 is always the label.
      blockList = divideString(line,' ');
      opor = blockList[label];
      
      argCount = directives::get(opor)-1+label;
      args = new std::string[argCount];
      if (label) args[0] = blockList[0];
      //For nonzero arguments, go one by one through the directive's demanded operands.
      for (int i = 1; i <= argCount; i++) args[i] = blockList[label+i];
      directives::process(opor,args);
      delete[] args;
    case 0://Exception.  NBD here.
      continue;
  }//end switch
}//end pass one

for (line in file){
  state = lineCase::passTwo(line);
  label = state % 2;
  
  switch (state - label){
    case 1://Directive.  Do nothing.
      continue;
    case 3://Instruction.  Grab object code and... do something with it.
      block = objectCode(line);
    case 5://Macro.  Expand it.
      macros::expand(line);
    case 0://Exception.  Now we worry.
      throw UnrecognizedLineException(line);
  }//end switch
}//end pass two

}//end namespace

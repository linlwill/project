


std::string* args;
std::string block;
LinkedList<std::string> blockList;
int label, state, workingBlock, argCount;

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
    case 1://Instruction.  Do nothing.
      continue;
    case 3://Directive.  Operator is first block, or second if label. Operands follow.
      blockList = divideString(line,' ');
      block = blockList[label];
      
      argCount = directives::get(block)-1;
      args = new std::string[argCount];
      for (int i = 0; i < argCount; i++) args[i] = blockList[label+i];
      directives::process(block,args);
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

namespace primary {
  
int CurrentAddress;
int startingAddress;
std::string startLabel;
  
std::string* args;
std::string opor;
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
    case 1://Instruction.  Increment current location by instruction mode + e of the line
      blockList = divideString(line,' ');
      opor = blockList[label];
      
      CurrentAddress += (instructions::get(opor).format + fb::e(line,false) );
    case 3://Directive.  Operator is first block, or second if label. Operands follow.  0 is always the label.
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
    case 5://Macro.  Start grabbing lines.
        //Not implemented yet!
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
      block = objectCode(line,label);
    case 5://Macro.  Expand it.
      macros::expand(line);
    case 0://Exception.  Now we worry.
      throw UnrecognizedLineException(line);
  }//end switch
}//end pass two

}//end namespace

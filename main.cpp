#include "LineCase.h"
#include "ObjectCodeGenerator.h"
#include <fstream>
#include <iostream>

class fileError {
    public:
        fileError(std::string text = ""){
            std::cout << text << std::endl;
        }
}//end class

int main(int argCount, char** args){
    //Arg 0 is file name.  Arg 1 is input file.  Arg 2, if it exists, is output file, default to out.o
    ifstream inFile;
    ofstream outFile;
    if (argCount < 1) throw fileError("No input file");
    
    //Open the files
    inFile.open(args[1]);
    if (argCount > 1) outFile.open(args[2]);
    else outFile.open("out.o");
    
    //Each line of the input file is a line of code.  Partition it as such.
    LinkedList<std::string> linesOfCode = LinkedList<std::string>();
    std::string line;
    //Dont worry about code yet, just make a list of lines
    while(!inFile.eof()){
        getline(inFile,line);
        if (line != "") linesOfCode.add(line);
    }//end while
    inFile.close();
    
    //Okay, NOW worry about code.
    int state,label;
    for (int i = 0; i < linesOfCode.getLength(); i++){
        line = linesOfCode[i];
        state = lineCase::passOne(line);
        label = state % 2;
        
        //Even states are the same as their odds, but they have labels.  Switches are the devil.
        state -= label;
        if (state == 1){
            //Increment current location by instruction mode + e of the line
            blockList = divideString(line,' ');
            opor = blockList[label];
            
            //If a reservation, find out how many to res
            int resCount = 1;
            if (opor.substr(0,3) == "RES")
                resCount = primary::forceInt(blockList[label+1]);
              
            CurrentAddress += instructions::sizeOf(opor,resCount);
        }//end if-instruction
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
          }//end if-directive
          else if (state == 5){
              //Macro.  Start grabbing lines.
              //Not implemented yet!
          }
    }//End pass One
        
    //Pass Two.  Convert each instruction into machine code and pass it to the file.  There's also the task of generating modification records but we're not there yet.
    for (int i = 0; i < linesOfCode.getLength(); i++){
          line = linesOfCode[i];
          state = lineCase::passTwo(line);
          label = state % 2;
          state -= label;
          
          if (state == 1){
              //Directive.  We did that above.
              continue;
          } else if (state == 3){
              //Instruction.  Party time!
              block = objectCode(line,label);
          } else if (state == 5){
              //Macro.  Not implemented.
          } else throw fileExeption("Bad line case: \n"+line);
          outFile << objectCode;
    }//end pass two
    outFile.close();
    
}//end main

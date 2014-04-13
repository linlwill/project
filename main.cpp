#include "LineCase.h"
#include "ObjectCodeGenerator.h"
#include <iostream>
#include "primary.h"
#include "Modification.h"
#include "Text.h"

class FileException {
    public:
        FileException(std::string text = ""){
            std::cout << text << std::endl;
        }
};//end class

int main(int argCount, char** args){
    //Arg 0 is file name.  Arg 1 is input file.  Arg 2, if it exists, is output file, default to out.o
    if (argCount < 1) throw FileException("No input file");

    //Open the files
    std::ifstream inFile;
    //inFile.open(args[1]);
    inFile.open("testInput.txt");
    if (argCount > 1) primary::outFile.open(args[2]);
    else primary::outFile.open("out.txt");

    //Each line of the input file is a line of code.  Partition it as such.
    LinkedList<std::string> linesOfCode = LinkedList<std::string>();
    std::string line;
    //Dont worry about code yet, just make a list of lines
    while(!inFile.eof()){
        getline(inFile,line);
        if (line != ""){
        ////std::cout << "Adding " << line << " to the list" << std::endl;
        linesOfCode.add(line);}
    }//end while
    inFile.close();

    ////std::cout << "Total of " << linesOfCode.getLength() << " lines in the list."<< std::endl;

    //Okay, NOW worry about code.

    int state,label;
    std::string opor;
    for (int i = 0; i < linesOfCode.getLength(); i++){
        ////std::cout << "In pass one, grabbing line " << i << std::endl;
        line = linesOfCode[i];
        ////std::cout << "Line is " << line << std::endl;
        state = lineCase::passOne(line);
        label = state % 2;
        // even % 2 = 0.  Odd % 2 = 1

        //odd states are the same as their evens, but they have labels.  Switches are the devil.
        ////std::cout << "State from " << line << " is " << state << " With label value " << label << std::endl;

        ///1,2 = instruction.    3,4 = directive.    0 = unknown.    odd -> has a label.
        state += label;
        if (state == 2){
            //Increment current location by instruction mode + e of the line
            LinkedList<std::string> blockList = divideString(line,' ');
            opor = blockList[label];

            //If a reservation, find out how many to res
            int resCount = 1;
            if (opor.substr(0,3) == "RES")
                resCount = primary::forceInt(blockList[label+1]);

            primary::CurrentAddress += instructions::sizeOf(opor,resCount);
        }//end if-instruction
        else if (state == 4){
              //Directive.  Operator is first block, or second if label. Operands follow.  0 is always the label.
              LinkedList<std::string> blockList = divideString(line,' ');
              opor = blockList[label];

              //0 will be label, or empty.  1... will be arguments, the amount of which is dictated by the directive.  Get thus dictates how many things to grab, b/c the extra 1 that exists so 1 can be 0 and 0 can be n/a compensates for the label.  I love when stuff synergizes.
              argCount = directives::get(opor);
              std::string* args = new std::string[argCount];
              if (label) args[0] = blockList[0];
              //For nonzero arguments, go one by one through the directive's demanded operands.  It's possible to run out of blocks here, like BASE asking for one but allowing none, so use LinkedList's exception handling.
              try{
                 for (int i = label+1; i < argCount; i++) args[i] = blockList[i];
              } catch(NotInListException){
                 //Cricket sounds.  new[] initializes the spaces to "", so passing as-is preserves empties as flags.
              }//end exceptions
              directives::process(opor,args);
              delete[] args;
          }//end if-directive
          else if (state == 6){
              //Macro.  Start grabbing lines.
              //Not implemented yet!
          }
    }//End pass One

    //Pass Two.  Convert each instruction into machine code and pass it to the file. Begin with the header record.
    //H(1) + name(6) + starting address(6) + length(6) + endl
    while(primary::programName.length() < 6) primary::programName += ' ';
    primary::outFile << "H" << primary::programName.substr(0,6) << Hex(primary::startingAddress).getHex(6) << Hex(primary::programLength).getHex(6) << '\n';
    std::string code;

    for (int i = 0; i < linesOfCode.getLength(); i++){
           // //std::cout << "In pass two" << std::endl;
          line = linesOfCode[i];
          state = lineCase::passTwo(line);
          label = state % 2;

          ////std::cout << "State from " << line << " is " << state << std::endl;
          state += label;


          if (state == 2){
              //Directive.  We did that above.
              continue;
          } else if (state == 4){
              //Instruction.  Party time!
              textRec::push( objectCode(line,label) );
          } else if (state == 6){
              //Macro.  Not implemented.
          } else throw FileException("Bad line case: \n"+line);
    }//end pass two

    //Pass the text records, the modification records, and then make/pass the end record
    textRec::push("!END!");
    while(textRec::notEmpty())
        primary::outFile << textRec::pull() << '\n';
    while(modRec::notEmpty())
        primary::outFile << modRec::pull() << '\n';

    //End record: E + starting address(6)
    primary::outFile << 'E' << Hex(primary::startingAddress).getHex(6);

    primary::outFile.close();

}//end main

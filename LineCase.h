#ifndef LINECASE_INCLUDED
#define LINECASE_INCLUDED
#include "DivideString.h"
#include "primary.h"
#include "Instructions.h"
#include "Directives.h"
#include <iostream>

#define UPDATE_BLOCK block = blockList[workingBlock++]

namespace lineCase{

bool isNumber(char c){
    return ((c >= '0') && (c <= '9'));
}//end isNumber

//isValid is shorthand for checking if an output is not the default answer.    Maps throw defaults on nonexistants, so this is how I check if something's part of a list.
bool isValid(std::string a){
    return (a == "");
}//end string
bool isValid(int a){
    return a;
}//end int
bool isValid(Instruction a){
    return a.isValid();
}//end instruction

int passOne(std::string& line){
    //1,2 = instruction.    3,4 = directive.    0 = unknown.    odd -> has a label.
    LinkedList<std::string> blockList = divideString(line,' ');
    int blockCount = blockList.getLength();
    ////std::cout << "In P1 line case dealing with " << line << ", a line of " << blockCount << " blocks." << std::endl;
    int workingBlock = 0;
    std::string block;
    std::string* label;
    //Special: line numbers are included.    Strip them from the string.
    if (isNumber(blockList[0][0])){
        //std::cout << "Handling line numbers" << std::endl;
        int end = line.length();
        for (int j = 0; j < end; j++){
            //cut up to first nonspace, non number.
            if ((line[j] != ' ') && !isNumber(line[j])){
                line = line.substr(j,end);
            }//end if
        }//end for
        workingBlock--;
    }//end purge of line numbers

    //Move to next block.    Check if it is an instruction or a directive.
    UPDATE_BLOCK;

    if (isValid(instructions::get(block))) return 2;
    if (isValid(directives::get(block))) return 4;

    //If neither directive or instruction, handle as a label, add it to the table.
    ////std::cout << "Adding " << block << " as a label" << std::endl;
    primary::labelTable[block] = primary::CurrentAddress;
    //If current is 0, it can cause problems with verification.
    if (primary::CurrentAddress == 0) primary::startLabel = block;


    //Move to the next block. Check again for instruction or directive.
    UPDATE_BLOCK;

    if (isValid(instructions::get(block))) return 1;
    if (isValid(directives::get(block))) return 3;

    //If we're here, we're dealing with an unknown.    That's fine, we could be seeing a macro invocation that isn't called until later.    Return as unknown.
    return 0;
}//end pass one

int passTwo(std::string line){
    //1,2 = directive.    3,4 = instruction.    5,6 = macro invocation.    odd -> has a label.
    //Don't need reference here because line numbers will have been purged in pass one.
    LinkedList<std::string> blockList = divideString(line,' ');
    ////std::cout << "In P2 line case dealing with " << line << " a line of " << blockList.getLength() << " blocks." << std::endl;
    int workingBlock = 0;
    std::string block = blockList[workingBlock];
    bool label = false;
    int state;

    //Firstly: is it a label?    If so, ignore.
    if (isValid(primary::labelTable[block]) || (block == primary::startLabel)){
        ////std::cout << "In the label if because of " << block << std::endl;
        workingBlock++;
        UPDATE_BLOCK;
        ////std::cout << "Now the block is " << block << std::endl;
        label = true;
    }//end label case

    ////std::cout << "This block is the operative one: " << block << std::endl;

    //Next, is it ia directive?    If so, state is 1 or 2 depending on if there's a label.
    if (isValid(directives::get(block))) return label ? 1 : 2;

    //Next, is it an instruction?    If so, great, return 3 or 4 on label state.
    if (isValid(instructions::get(block))) return label ? 3 : 4;

    //Return 5 or 6 if it's a macro invocation
    //if (isValid(macros::get(block))) return label ? 5 : 6;

    //At this point it is not a directive, macro call, or instruction.    Error state.
    return 0;
}//end pass two

}//end namespace
#endif

#ifndef PRIMARY_INCLUDED
#define PRIMARY_INCLUDED
#include <map>
#include <string>
#include "LinkedList.h"
#include "Hex.h"

namespace primary{
    std::map<std::string,int> labelTable;
    int CurrentAddress, startingAddress, label, state, workingBlock, argCount;
    std::string startLabel;
    
    
    int forceInt(std::string input){
        //Evaluate based on integer, hexidecimal, binary, {char, or arithmatic} input.
        std::string id = input.substr(0,2);
        if (id == "X'") return Hex.toInt(input.substr(2,input.length()-1));
        else if (id == "B'") return Hex.toInt("B"+input.substr(2,input.length()-1));
        else return Hex.toInt("I"+input);
    }//end force-int
}
#endif

#ifndef PRIMARY_INCLUDED
#define PRIMARY_INCLUDED
#include <map>
#include <string>
#include "LinkedList.h"
#include "Hex.h"
#include <sstream>
#include <fstream>
#include "Modification.h"

namespace primary{
    std::map<std::string,int> labelTable;
    int CurrentAddress, startingAddress, label, state, workingBlock, argCount, programLength;
    std::string startLabel, programName;
    std::ofstream outFile;

    int forceInt(std::string input){
        //Evaluate based on integer, hexidecimal, binary, {char, or arithmatic} input.
        std::string id = input.substr(0,2), working;
        if (id == "X'"){
            //Grab the significant characters and pass it to Hex's toInt
            working = input.substr(2,input.length()-3);
            return Hex::toInt(working);
        } else if (id == "B'"){
            //The same but tack on a B as a binary flag for Hex's function
            working = input.substr(2,input.length()-3);
            working = "B"+working;
            return Hex::toInt(working);
        } else {
            //Run as integer
            int temp;
            std::stringstream(input) >> temp;
            return temp;
        }
    }//end force-int
}

#endif

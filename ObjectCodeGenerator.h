#ifndef OBJECTCODEMAKER_INCLUDED
#define OBJECTCODEMAKER_INCLUDED

#include "StringDemarkation.h"
#include "Instructions.h"
#include "FlagBits.h"
#include "SymbolTable.h"
#include <sstream>
//From a line of assembly code, return a hexidecimal string corresponding to the machine-code equivilent.
//No preview, because only a single function: string objectCode(string lineOfCode, int currentAddress).  LabelTable is here because it is referenced here.  It won't be here in the long run.
SymbolTable LabelTable = SymbolTable();

std::string objectCode(std::string lineOfCode, int currentAddress){
    //Determine the instruction mode.  This will dictate the rest of the show.
    LinkedList<std::string> strBlocks = divideString(lineOfCode,' ');
    std::string objCode = "";
    std::string opor;
    std::string opand;
    std::string label = "";
    int blockCount = strBlocks.getLength();

    if (blockCount == 3){
        //indexing in the list is backwards.  Last is first.
        label = strBlocks[2];
        opor = strBlocks[1];
        opand = strBlocks[0];
    } else if (blockCount == 2) {
        opor = strBlocks[1];
        opand = strBlocks[0];
        //There's a possibility here of a mode1 instruction with a label.  If that's the case, opor is [0] and label is [1]
        if (getInstruction(opand).format == 1){
            opor = strBlocks[0];
            label = strBlocks[1];
        }//end exception
    } else if (blockCount == 1){
        opor = strBlocks[0];
    } else return "!!! ERROR IN DIVIDING STRING FOR OBJECT CODE !!!";
    //end define segments

    //Run e now so the non+ operator can be passed into getInstruction.  Error if not in mode 3 afterwards
    char e = fb::e(&opor);
    Instruction theInst = getInstruction(opor);
    if ( (e == '1') && (theInst.format != 3) ) return "!!! ERROR: EXTENDED FORMAT USED IN NON-EXTENDABLE INSTRUCTION !!!";

    if (theInst.format == 1){
        return theInst.opcode.getHex();
    }//end mode 1 - easy mode

    else if (theInst.format == 2){
        Reg::initDB();
        objCode += theInst.opcode.getHex();
        //Operand will be the two registers to act on demarked by ,
        LinkedList<std::string> registers = divideString(opand,',');
        if (registers.getLength() != 2) return "!!! ERROR: INVALID OPERAND FOR TYPE-2 INSTRUCTION !!!";
        std::string R1 = registers[1];
        std::string R2 = registers[0];
        //Add each register's value in hex to the string.
        if ( (!Reg::DB.contains(R1)) && (!Reg::DB.contains(R2)) ) return "!!! ERROR: UNRECOGNIZED REGISTER IN MODE2 OBJECT CODE !!!";
        objCode += Hex(Reg::DB[R1]).getHex();
        objCode += Hex(Reg::DB[R2]).getHex();
    }//end mode 2 - Medium mode

    else if (theInst.format == 3){
        //Address is what we WANT, not what we NEED.  However, flagbits' bp() converts them silently.
        std::string nix = fb::nix(&opand);
        std::string bp;

        int address;
        //Convert operand into a numerical address.  What we "want".  If it's a number, just conver it to an int as-is.
        if ((opand[0] >= '0') && (opand[0] <= '9')) std::stringstream(opand) >> address;
        else if (LabelTable.contains(opand)) address = LabelTable[opand];
        else return "!!! ERROR: UNRECOGNIZED LABEL IN MODE3 OBJECT CODE !!!";

        //If we're in I or E, we don't need b or p.  Otherwise, we do.
        if ((nix[1]-'0')||(e-'0')) bp = "00";
        else bp = fb::bp(&address,currentAddress);

        //nixbpe have been set, and opor and opand have been modified accordingly.  Assemble the string.
        Hex opcode = theInst.opcode;
        std::string bin = "B";
        bin+= nix[0];
        bin += nix[1];
        opcode += bin;

        bin = "B";
        bin += nix[2];
        bin += bp;
        bin += e;
        Hex xbpe = Hex(bin);

        std::string finalAddr = Hex(address).getHex();
        int len = 3 + (e - '0')*2;
        while (finalAddr.length() < len) finalAddr = '0'+finalAddr;

        objCode += (opcode.getHex()+xbpe.getHex()+finalAddr);
    }//end mode 3 - Hard mode

    return objCode;
}
#endif

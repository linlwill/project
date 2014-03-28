#ifndef OBJECTCODEMAKER_INCLUDED
#define OBJECTCODEMAKER_INCLUDED

#include "DivideString.h"
#include "Instructions.h"
#include "FlagBits.h"
#include <map>
#include <sstream>
//From a line of assembly code, return a hexidecimal string corresponding to the machine-code equivilent.
//No preview, because only a single function: string objectCode(string lineOfCode, int currentAddress).  LabelTable is here because it is referenced here.  It won't be here in the long run.
map<std::string,int> LabelTable;

class CodeGenerationException {
    public:
        std::string errorCode;
        Exception(std::string text){
            errorCode = text;
        }//end constructor
};//end exception

std::string objectCode(std::string lineOfCode, int hasLabel){
    //Determine the instruction mode.  This will dictate the rest of the show.
    LinkedList<std::string> strBlocks = divideString(lineOfCode,' ');
    std::string objCode = "";
    int blockCount = strBlocks.getLength();
    
    Instruction theInst = instruction::get(strBlocks[hasLabel]);
    std::string opand = strBlocks[hasLabel+1];

    //Run e now.  Error if not in mode 3 and e
    int e = fb::e(&opor);
    if ( e && (theInst.format != 3) ) throw CodeGenerationException("EXTENDED FORMAT USED IN NON-EXTENDABLE INSTRUCTION");

    switch(theInst.format){
        case 1:
            objCode = theInst.opcode.getHex(2);
        case 2:
            objCode += theInst.opcode.getHex(2);
            //Operand will be the two registers to act on demarked by ,
            LinkedList<std::string> registers = divideString(opand,',');
            if (registers.getLength() != 2) throw CodeGenerationException("INVALID OPERAND FOR TYPE-2 INSTRUCTION !!!";
            std::string R1 = registers[0];
            std::string R2 = registers[1];
            //Add each register's value in hex to the string.
            objCode += Hex(reg::get(R1)).getHex();
            objCode += Hex(reg::get(R2)).getHex();
        case 3:
            //Address is what we WANT, not what we NEED.  However, flagbits' bp() converts them silently.
            std::string nix = fb::nix(&opand);
            std::string bp;
    
            int address;
            //Convert operand into a numerical address.  What we "want".  If it's a number, just conver it to an int as-is.
            if ((opand[0] >= '0') && (opand[0] <= '9')) std::stringstream(opand) >> address;
            else if (LabelTable[opand] || (::startLabel == opand)) address = LabelTable[opand];
            else throw CodeGenerationException("UNRECOGNIZED LABEL IN MODE3 OBJECT CODE");
    
            //If we're in I or E, we don't need b or p.  Otherwise, we do.
            if ( (nix[1]-'0') || e ) bp = "00";
            else bp = fb::bp(&address,::CurrentAddress);
    
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
    
            int len = 3 + (e - '0')*2;
            std::string finalAddr = Hex(address).getHex(len);
    
            objCode += (opcode.getHex(2)+xbpe.getHex()+finalAddr);
        default:
            throw CodeGenerationException("INVALID INSTRUCTION MODE");
    }//end switch

    return objCode;
}
#endif

#ifndef OBJECTCODEMAKER_INCLUDED
#define OBJECTCODEMAKER_INCLUDED

#include "DivideString.h"
#include "Instructions.h"
#include "FlagBits.h"
#include "primary.h"

//From a line of assembly code, return a hexidecimal string corresponding to the machine-code equivilent.
//No preview, because only a single function: string objectCode(string lineOfCode, int currentAddress).  LabelTable is here because it is referenced here.  It won't be here in the long run.

class CodeGenerationException {
    public:
        std::string errorCode;
        CodeGenerationException(std::string text){
            errorCode = text;
        }//end constructor
};//end exception

std::string objectCode(std::string lineOfCode, int hasLabel){
    //Determine the instruction mode.  This will dictate the rest of the show.
    LinkedList<std::string> strBlocks = divideString(lineOfCode,' ');
    std::string objCode = "";
    std::string opor = strBlocks[hasLabel];
    int blockCount = strBlocks.getLength();

    Instruction theInst = instructions::get(opor);
    std::string opand;//Only grab opand if we need it
    if (blockCount > 1) opand = strBlocks[hasLabel+1];

    //Run e now.  Error if not in mode 3 and e
    int e = fb::e(opor);
    if ( e && (theInst.format != 3) ) throw CodeGenerationException("EXTENDED FORMAT USED IN NON-EXTENDABLE INSTRUCTION");


    //Begin case branching.  Screw you switches.
    int resCount = 1;
    if (theInst.format == 0){
        //Memory management.  Size is how many bytes it takes.
        int size = theInst.opcode.value;
        int value = primary::forceInt(opand);
        if (opor.substr(0,3) == "RES"){
            //Reservation.  Return a newline and begin a new text record.  Record the count.
            resCount = value;
            objectCode = "\nT";
        } else {
            //Assignment.  Opand is what to initialize to.  Return opand's value in hex, occupying however much space it should.
            objectCode = Hex(value).getHex(size);
        }//end else
    }//end case 0: memory

    else if (theInst.format == 1) objCode = theInst.opcode.getHex(2);

    else if (theInst.format == 2){
        objCode += theInst.opcode.getHex(2);
        LinkedList<std::string> registers = divideString(opand,',');
        if (registers.getLength() != 2) throw CodeGenerationException("INVALID OPERAND FOR TYPE-2 INSTRUCTION");
        objCode += Hex(reg::get(registers[0])).getHex();
        objCode += Hex(reg::get(registers[1])).getHex();
    }//End case 2
    else if (theInst.format == 3){
        //Address is what we WANT, not what we NEED.  However, flagbits' bp() converts them silently.
        std::string nix = fb::nix(opand);
        std::string bp;

        int address;
        //Convert operand into a numerical address.  What we "want".  If it's a number prefixed with =, just conver it to an int as-is.
        if (opand[0] == '='){
            //Literal.  Don't mess around with labels, use opand as value
            opand.erase(0,1);
            address = primary::forceInt(opand);
        }//end literal
        else if (primary::labelTable[opand] || (primary::startLabel == opand)) address = primary::labelTable[opand];
        else throw CodeGenerationException("UNRECOGNIZED LABEL IN MODE 3 OBJECT CODE");

        //If we're in I or E, we don't need b or p.  Otherwise, we do.
        if ( (nix[1]-'0') || e ) bp = "00";
        else bp = fb::bp(address, primary::CurrentAddress);

        //nixbpe have been set, and opor and opand have been modified accordingly.  Assemble the string.
        Hex opcode = theInst.opcode;
        std::string bin = "B";
        bin+= nix[0];
        bin += nix[1];
        opcode += bin;


        bin = "B";
        bin += nix[2];
        bin += bp;
        bin += e ? '1':'0';

        Hex xbpe = Hex(bin);

        int len = 3 + e*2;
        std::string finalAddr = Hex(address).getHex(len);

        objCode += (opcode.getHex(2)+xbpe.getHex()+finalAddr);
    }//end case 3

    //Step ahead however many bytes we just took up.  
    //primary::CurrentAddres += e + theInst.format;
    primary::CurrentAddres += instructions::sizeOf(theInst,resCount);
    return objCode;
}
#endif

#ifndef TEXTRECORD_INCLUDED
#define TEXTRECORD_INCLUDED
#include <string>
#include <iostream>
#include "Queue.h"
namespace textRec {
    Queue<std::string> records = Queue<std::string>();
    std::string openRecord = "";
    Hex startAddr = Hex();

    void push(std::string code){
        //std::cout << "Push called for " << code << std::endl << "Open record is currently " << openRecord << std::endl << "Current address is " << primary::CurrentAddress << " while start address (in decimal) is " << startAddr.value << std::endl;
        if (code == "!END!"){
            //A reservation, or other call to end the text record, has been encountered.  Package it all up and push to the queue.
            if (openRecord == "") return;
            int finalLength = primary::CurrentAddress - startAddr.value;
            ////std::cout << "Final length is " << primary::CurrentAddress << '-' << startAddr.value << '=' << finalLength << std::endl;
            std::string finalCode;
            //T + starting address(6) + length in bytes(2) + text(60).  2-byte length means max bytes is 255, which is being rounded down to 240, aka f0 or 60 hex characters.
            while(finalLength > 240){
                finalLength -= 240;
                finalCode = "T" + startAddr.getHex(6) + "^f0^" + openRecord.substr(0,60) + "^";
                ////std::cout << "Final code from " << code << " is " << finalCode << std::endl;
                startAddr += 240;
                records.push(finalCode);
            }//end while
            finalCode = "T" + startAddr.getHex(6) + "^" + Hex(finalLength).getHex(2) + "^" + openRecord;
            ////std::cout << "Final code from " << code << " is " << finalCode << std::endl;
            records.push(finalCode);
            openRecord = "";
        }//end if
        else {
            //If no open record, start one.  It's starting address is the current address minus the current block's length (b/c that was the address when this code began to be written)
            //code is a hex string, each hex string is half a byte.
            if (openRecord == "") startAddr = Hex(primary::CurrentAddress - code.length()/2);
            openRecord += code;
        }//end else
    }//end push

    std::string pull(){
        return records.pull();
    }//end string

    bool notEmpty(){
        return records.notEmpty();
    }//end bool

}//end namespace
#endif


#ifndef TRANSLATOR_INCLUDED
#define TRANSLATOR_INCLUDED
#include <string>
#include "Hex.h"
using namespace std;

class Instruction {
  public:
    string keyword;
    int format;
    Hex opcode;
    
    Instruction(){
      keyword = 0;
      format = 0;
      opcode = 0;
    }//end constructor
    
    Instruction(string keyword, int format, string opcode){
      Instruction::keyword = keyword;
      Instruction::format = format;
      Instruction::opcode = Hex(opcode);
    }//end good constructor
};

Instruction[59] instructionDB = {
		Instruction("ADD",3,"18"),
		Instruction("ADDF",3,"58"),
		Instruction("ADDR",2,"90"),
		Instruction("AND",3,"40"),
		Instruction("CLEAR",2,"B4"),
		Instruction("COMP",3,"28"),
		Instruction("COMPF",3,"88"),
		Instruction("COMPR",2,"A0"),
		Instruction("DIV",3,"24"),
		Instruction("DIVF",3,"64"),
		Instruction("DVIR",2,"9C"),
		Instruction("FIX",1,"C4"),
		Instruction("FLOAT",1,"C0"),
		Instruction("HIO",1,"F4"),
		Instruction("J",3,"3C"),
		Instruction("JEQ",3,"30"),
		Instruction("JGT",3,"34"),
		Instruction("JLT",3,"38"),
		Instruction("JSUB",3,"48"),
		Instruction("LDA",3,"00"),
		Instruction("LDB",3,"68"),
		Instruction("LDCH",3,"50"),
		Instruction("LDF",3,"70"),
		Instruction("LDL",3,"08"),
		Instruction("LDS",3,"6C"),
		Instruction("LDT",3,"74"),
		Instruction("LDX",3,"04"),
		Instruction("LPS",3,"D0"),
		Instruction("MUL",3,"20"),
		Instruction("MULF",3,"60"),
		Instruction("MULR",2,"98"),
		Instruction("NORM",1,"C8"),
		Instruction("OR",3,"44"),
		Instruction("RD",3,"D8"),
		Instruction("RMO",2,"AC"),
		Instruction("RSUB",3,"4C"),
		Instruction("SHIFTL",2,"A4"),
		Instruction("SHIFTR",2,"A8"),
		Instruction("SIO",1,"F0"),
		Instruction("SSK",3,"EC"),
		Instruction("STA",3,"0C"),
		Instruction("STB",3,"78"),
		Instruction("STCH",3,"54"),
		Instruction("STF",3,"80"),
		Instruction("STI",3,"D4"),
		Instruction("STL",3,"14"),
		Instruction("STS",3,"7C"),
		Instruction("STSW",3,"E8"),
		Instruction("STT",3,"84"),
		Instruction("STX",3,"10"),
		Instruction("SUB",3,"1C"),
		Instruction("SUBF",3,"5C"),
		Instruction("SUBR",2,"94"),
		Instruction("SVC",2,"B0"),
		Instruction("TD",3,"E0"),
		Instruction("TIO",1,"F8"),
		Instruction("TIX",3,"2C"),
		Instruction("TIXR",2,"B8"),
		Instruction("WD",3,"DC")
	};//End array of instructions
	
Instruction getInstruction(string subject){
  //If subject is in instructionDB's keywords, return the corresponding instance.  Else return 0.
  for (int i = 0; i < 59; i++){
    if (subject == instructionDB[i].keyword) return instructionDB[i];
  }//end for
  return 0;
}//end getInstruction=

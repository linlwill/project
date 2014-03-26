#ifndef INSTRUCTIONS_INCLUDED
#define INSTRUCTIONS_INCLUDED
#include <string>
#include "Hex.h"
#include <map>

class Instruction {
  public:
    //std::string keyword;
    int format;
    Hex opcode;

    Instruction(){
    	//Cricket sounds
    }//end constructor

    Instruction(/*std::string keyword, */int format, std::string opcode){
      //Instruction::keyword = keyword;
      Instruction::format = format;
      Instruction::opcode = Hex(opcode);
    }//end good constructor
};
/*
namespace Reg {
	SymbolTable DB = SymbolTable();
	bool DBisOn = false;
	void initDB(){
	    if (Reg::DBisOn) return;
	    Reg::DBisOn = true;
	    DB.add("A",0);
	    DB.add("X",1);
	    DB.add("L",2);
	    DB.add("PC",8);
	    DB.add("SW",9);
	    DB.add("B",3);
	    DB.add("S",4);
	    DB.add("T",5);
	    DB.add("F",6);
	}//end blatant hack
}//end namespace
*/

namespace Reg {
	map<std::string,int> DB;
	bool DBisOn = false;
	void initDB(){
		if (Reg::DBisOn) return;
		Reg::DBisOn = true;
		DB["A"] = 0;
		DB["X"] = 1;
		DB["L"] = 2;
		DB["PC"] = 8;
		DB["SW"] = 9;
		DB["B"] = 3;
		DB["S"] = 4;
		DB["T"] = 5;
		DB["F"] = 6;
	}//end init
}//end namespace
/*
Instruction instructionDB[59] = {
		Instruction("ADD",3,"18"),
		Instruction("ADDF",3,"58"),
		Instruction("ADDR",2,"90"),
		Instruction("AND",3,"40"),
		Instruction("CLEAR",2,"b4"),
		Instruction("COMP",3,"28"),
		Instruction("COMPF",3,"88"),
		Instruction("COMPR",2,"a0"),
		Instruction("DIV",3,"24"),
		Instruction("DIVF",3,"64"),
		Instruction("DVIR",2,"9c"),
		Instruction("FIX",1,"c4"),
		Instruction("FLOAT",1,"c0"),
		Instruction("HIO",1,"f4"),
		Instruction("J",3,"3c"),
		Instruction("JEQ",3,"30"),
		Instruction("JGT",3,"34"),
		Instruction("JLT",3,"38"),
		Instruction("JSUB",3,"48"),
		Instruction("LDA",3,"00"),
		Instruction("LDB",3,"68"),
		Instruction("LDCH",3,"50"),
		Instruction("LDF",3,"70"),
		Instruction("LDL",3,"08"),
		Instruction("LDS",3,"6c"),
		Instruction("LDT",3,"74"),
		Instruction("LDX",3,"04"),
		Instruction("LPS",3,"d0"),
		Instruction("MUL",3,"20"),
		Instruction("MULF",3,"60"),
		Instruction("MULR",2,"98"),
		Instruction("NORM",1,"c8"),
		Instruction("OR",3,"44"),
		Instruction("RD",3,"d8"),
		Instruction("RMO",2,"ac"),
		Instruction("RSUB",3,"4c"),
		Instruction("SHIFTL",2,"a4"),
		Instruction("SHIFTR",2,"a8"),
		Instruction("SIO",1,"f0"),
		Instruction("SSK",3,"ec"),
		Instruction("STA",3,"0c"),
		Instruction("STB",3,"78"),
		Instruction("STCH",3,"54"),
		Instruction("STF",3,"80"),
		Instruction("STI",3,"d4"),
		Instruction("STL",3,"14"),
		Instruction("STS",3,"7c"),
		Instruction("STSW",3,"e8"),
		Instruction("STT",3,"84"),
		Instruction("STX",3,"10"),
		Instruction("SUB",3,"1c"),
		Instruction("SUBF",3,"5c"),
		Instruction("SUBR",2,"94"),
		Instruction("SVC",2,"b0"),
		Instruction("TD",3,"e0"),
		Instruction("TIO",1,"f8"),
		Instruction("TIX",3,"2c"),
		Instruction("TIXR",2,"b8"),
		Instruction("WD",3,"dc")
	};//End array of instructions
*/

namespace instruction {
	map<std::string,Instruction> DB;
	bool DBinitialized = false;
	void initDB(){
		if (DBinitialized) return;
		instruction::DBinitialized = true;
		DB["ADD"]=Instruction(3,"18");
		DB["ADDF"]=Instruction(3,"58");
		DB["ADDR"]=Instruction(2,"90");
		DB["AND"]=Instruction(3,"40");
		DB["CLEAR"]=Instruction(2,"b4");
		DB["COMP"]=Instruction(3,"28");
		DB["COMPF"]=Instruction(3,"88");
		DB["COMPR"]=Instruction(2,"a0");
		DB["DIV"]=Instruction(3,"24");
		DB["DIVF"]=Instruction(3,"64");
		DB["DVIR"]=Instruction(2,"9c");
		DB["FIX"]=Instruction(1,"c4");
		DB["FLOAT"]=Instruction(1,"c0");
		DB["HIO"]=Instruction(1,"f4");
		DB["J"]=Instruction(3,"3c");
		DB["JEQ"]=Instruction(3,"30");
		DB["JGT"]=Instruction(3,"34");
		DB["JLT"]=Instruction(3,"38");
		DB["JSUB"]=Instruction(3,"48");
		DB["LDA"]=Instruction(3,"00");
		DB["LDB"]=Instruction(3,"68");
		DB["LDCH"]=Instruction(3,"50");
		DB["LDF"]=Instruction(3,"70");
		DB["LDL"]=Instruction(3,"08");
		DB["LDS"]=Instruction(3,"6c");
		DB["LDT"]=Instruction(3,"74");
		DB["LDX"]=Instruction(3,"04");
		DB["LPS"]=Instruction(3,"d0");
		DB["MUL"]=Instruction(3,"20");
		DB["MULF"]=Instruction(3,"60");
		DB["MULR"]=Instruction(2,"98");
		DB["NORM"]=Instruction(1,"c8");
		DB["OR"]=Instruction(3,"44");
		DB["RD"]=Instruction(3,"d8");
		DB["RMO"]=Instruction(2,"ac");
		DB["RSUB"]=Instruction(3,"4c");
		DB["SHIFTL"]=Instruction(2,"a4");
		DB["SHIFTR"]=Instruction(2,"a8");
		DB["SIO"]=Instruction(1,"f0");
		DB["SSK"]=Instruction(3,"ec");
		DB["STA"]=Instruction(3,"0c");
		DB["STB"]=Instruction(3,"78");
		DB["STCH"]=Instruction(3,"54");
		DB["STF"]=Instruction(3,"80");
		DB["STI"]=Instruction(3,"d4");
		DB["STL"]=Instruction(3,"14");
		DB["STS"]=Instruction(3,"7c");
		DB["STSW"]=Instruction(3,"e8");
		DB["STT"]=Instruction(3,"84");
		DB["STX"]=Instruction(3,"10");
		DB["SUB"]=Instruction(3,"1c");
		DB["SUBF"]=Instruction(3,"5c");
		DB["SUBR"]=Instruction(2,"94");
		DB["SVC"]=Instruction(2,"b0");
		DB["TD"]=Instruction(3,"e0");
		DB["TIO"]=Instruction(1,"f8");
		DB["TIX"]=Instruction(3,"2c");
		DB["TIXR"]=Instruction(2,"b8");
		DB["WD"]=Instruction(3,"dc");		
	}//end init
	
	Instruction get(std::string label){
		initDB();
		return DB[label];
	}//end get
}//end namespace
/*
Instruction getInstruction(std::string subject){
  //If subject is in instructionDB's keywords, return the corresponding instance.  Else return 0.
  for (int i = 0; i < 59; i++){
    if (subject == instructionDB[i].keyword) return instructionDB[i];
  }//end for
  return Instruction();
}//end getInstruction
*/
#endif

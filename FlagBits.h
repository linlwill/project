//Using string pointers, identify the flag bits nixbpe and trim the strings of those flags.
//For b and p, need current location too, and this time need to work on address, not operand.  "Want" in the readme.

#ifndef FLAGBITS_INCLUDED
#define FLAGBITS_INCLUDED
#include <string>
#include "Base.h"

class OutOfRangeException{
    public:
        OutOfRangeException(){}
};//end exception

namespace fb {
///    string nix(string* operand);
///    char e(string* opor);
///    string pb(int* want, int current);

std::string nix(std::string* operand){
    std::string result = "000";
    if ((*operand)[0] == '#'){
        //immediate
        result[1] = '1';
        (*operand).erase(0,1);
    } else if ((*operand)[0] == '@'){
        //dereferenced
        result[0] = '1';
        (*operand).erase(0,1);
    }//end n/i

    char last = (*operand)[(*operand).length()-1];
    char nextToLast = (*operand)[(*operand).length()-2];

    if ((last == 'X')&&(nextToLast == ',')){
        result[2] = '1';
        int end = (*operand).length()-1;
        (*operand).erase(end-1,end);
    } return result;
}//end nix

char e(std::string* opor){
  if ((*opor)[0] != '+') return '0';
  else {
    (*opor).erase(0,1);
    return '1';
  }//end else
}//end e

std::string bp(int* want, int current){
  //Assume this is being called in the context of actually needing a b or a p, and knowing where we want to go.
  //b is unsigned, varying in [0,4095].  p is signed, varying in [-2048,2047]
  int variance = *want - current;
  if ((variance < 2047)&&(variance > -2048)){
    *want = variance;
    return "01";
  }//out of range for PC relative.  Maybe we can use Base.

  else if (Base::inBlock(current)){
    //Out of range for PC relative, but we're in a base block so there's hope.  No negatives tolerated here.
    unsigned int bvariance = *want - Base::getBase(current);
    if (bvariance < 4095){
      //Jackpot.  We can use Base addressing to reach the desired address.
      *want = bvariance;
      return "10";
    }//
  }//out of range for Base relative.  All hope is lost.

  throw OutOfRangeException();
}//end pb

}//end namespace
#endif

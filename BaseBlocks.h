#ifndef BASEBLOCKS_INCLUDED
#define BASEBLOCKS_INCLUDED
#include "LinkedList.h"
//Provide functions to begin and end base blocks, then later check if where they are is in a block and if so, what that block's value is
class BaseBlock{
  public:
  int startAddress;
  int value;
  int endAddress;
  
  BaseBlock(int a, int b){
    startAddress = a;
    value = b;
  }//end constructor
};//end class.  Would have been struct but class made LinkedList utilization easier.

bool openBaseBlock = false;
LinkedList<BaseBlock> BaseBlockList = LinkedList<BaseBlock>();

void startBaseBlock(int address, int value);
void endBaseBlock(int address);
bool inBaseBlock(int address);
int getBase(int address);

void startBaseBlock(int address, int value){
  //iff there isn't a block open already, open one with corresponding values.
  if (!openBaseBlock){
    openBaseBlock = true;
    BaseBlockList.add(BaseBlock(address,value));
  }//end if
}//end startblock

void endBaseBlock(int address){
  //iff there is an open block, grab to the top of the list and set its end to end.  Then close the block.
  if (openBaseBlock){
    openBaseBlock = false;
    (*BaseBlockList.top).content.endAddress = address;
  }//end if
}//end endblock

bool inBaseBlock(int address){
  //O(N) search of the base blocks checking if address is in bounds
  BaseBlock temp;
  for (int i = 0; i < BaseBlockList.getLength(); i++){
    temp = BaseBlockList[i];
    if ((address >= temp.beginAddress)&&(address <= temp.endAddress)) return true;
  }//end for
  return false;
}//end inblock

int getBase(int address){
  //Another search just like inblock.  This time return value.  Return -1 on not found, so this could be used as bool too.
  BaseBlock temp;
  for (int i = 0; i < BaseBlockList.getLength(); i++){
    temp = BaseBlockList[i];
    if ((address >= temp.beginAddress)&&(address <= temp.endAddress)) return temp.value;
  }//end for
  return -1;
}//end getBase

#endif

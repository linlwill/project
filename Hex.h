//This is a way to handle mathematics with strings, binary strings, integers, or other Hexs.
//At the moment, all that are supported are =, +, and +=. others wil be added as need arises.
#ifndef HEX_INCLUDED
#define HEX_INCLUDED
#include <string>
#include <math.h>
using namespace std;

class Hex {
  private:
    static const string hexDigits;
  public:
    static int toInt(string input);
    int value;
    string getHex();
    
    Hex();
    Hex(int start);
    Hex(string start);
    Hex(Hex start);
    
    int operator+(int add);
    int operator+(string add);
    int operator+(Hex add);
    
    void operator=(int get);
    void operator=(string get);
    void operator=(Hex get);
    
    void operator+=(int add);
    void operator+=(string add);
    void operator+=(Hex add);
};

const string Hex::hexDigits = "0123456789abcdef";

Hex::Hex(){
  value = 0;
} Hex::Hex(int start){
  value = start;
} Hex::Hex(string start){
  value = toInt(start);
} Hex::Hex(Hex start){
  value = start.value;
}//end constructors

int Hex::operator+(int add){
  return value+add;
} int Hex::operator+(string add){
  return value+toInt(add);
} int Hex::operator+(Hex add){
  return value+add.value;
}//end addition

void Hex::operator=(int get){
  value = get;
} void Hex::operator=(string get){
  value = toInt(get);
} void Hex::operator=(Hex get){
  value = get.value;
}//end assignment

void Hex::operator+=(int add){
  value += add;
} void Hex::operator+=(string add){
  value += toInt(add);
} void Hex::operator+=(Hex add){
  value += add.value;
}//end add-assign

string Hex::getHex(){
  //Divide value by 16.  The remainder is the rightmost digit.  Divide the quotient by 16.  Repeat.  When quo = 0, stop. Handle 0 as a special case.
  if (!value) return "0";
  int quo = value;
  int rem;
  string finished = "";
  while (quo){
    rem = quo % 16;
    quo = quo / 16;
    finished = hexDigits[rem] + finished;
  }//end while
  return finished;
}//end getHex

int Hex::toInt(string input){
  //Return the base-10 of input interpreted as hex.  If leading-char of input is B (NOT b), interpret as binary
  int result = 0;
  int count = 0;
  int digit;
  if (input[0] == 'B'){
    //Binary.  result += digit*2^count, but binary reads backwards so start at the end.
    for (int i = input.length()-1; i; i--){
      digit = input[i] - '0'; //Digit is now the true value of 0 or 1.
      result += digit*pow(2,count);
      count++;
    }//end for  
    return result;
  } else {
    //Hexadecimal - ID if letter or number.  If number, handle just like bin.  If letter, same but do - 87 since a=97.  Allow [0].
    for (int i = input.length()-1; i+1, i--){
      digit = input[i];
      if (digit >= 'a') digit -= 87;
      else digit -= '0';
      result += digit*pow(16,count);
      cout++;
    }//end for
    return result;
  }//end condition
}//end toInt

#endif

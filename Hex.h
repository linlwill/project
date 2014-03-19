//This is a way to handle mathematics with std::strings, binary std::strings, integers, or other Hexs.
//At the moment, all that are supported are =, +, ++, --, and +=. others wil be added as need arises.
#ifndef HEX_INCLUDED
#define HEX_INCLUDED
#include <string>
#include <math.h>

class Hex {
  private:
    static const std::string hexDigits;
  public:
    static int toInt(std::string input);
    int value;
    std::string getHex();
    std::string getHex(int len);

    Hex();
    Hex(int start);
    Hex(std::string start);
    Hex(const Hex& start);

    int operator+(int add);
    int operator+(std::string add);
    int operator+(Hex add);

    void operator=(int get);
    void operator=(std::string get);
    void operator=(Hex get);

    void operator+=(int add);
    void operator+=(std::string add);
    void operator+=(Hex add);

    void operator++(int inc);
    void operator--(int inc);
};

const std::string Hex::hexDigits = "0123456789abcdef";

Hex::Hex(){
  value = 0;
} Hex::Hex(int start){
  value = start;
} Hex::Hex(std::string start){
  value = toInt(start);
} Hex::Hex(const Hex& start){
  value = start.value;
}//end constructors

int Hex::operator+(int add){
  return value+add;
} int Hex::operator+(std::string add){
  return value+toInt(add);
} int Hex::operator+(Hex add){
  return value+add.value;
}//end addition

void Hex::operator=(int get){
  value = get;
} void Hex::operator=(std::string get){
  value = toInt(get);
} void Hex::operator=(Hex get){
  value = get.value;
}//end assignment

void Hex::operator+=(int add){
  value += add;
} void Hex::operator+=(std::string add){
  value += toInt(add);
} void Hex::operator+=(Hex add){
  value += add.value;
}//end add-assign

void Hex::operator++(int inc){
  //No idea why an integer argument was needed, but w/e
  value++;
}//end increment

void Hex::operator--(int inc){
  value--;
}//end decrement

std::string Hex::getHex(){
  //Divide value by 16.  The remainder is the rightmost digit.  Divide the quotient by 16.  Repeat.  When quo = 0, stop. Handle 0 as a special case.
  if (!value) return "0";
  unsigned int quo = value;
  int rem;
  std::string finished = "";
  while (quo){
    rem = quo % 16;
    quo = quo / 16;
    finished = hexDigits[rem] + finished;
  }//end while
  return finished;
}//end getHex

std::string Hex::getHex(int len){
  std::string temp = getHex();
  while (temp.length() < len) temp = '0'+temp;
  return temp;
}//end forced-length getHex

int Hex::toInt(std::string input){
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
    for (int i = input.length()-1; i+1; i--){
      digit = input[i];
      if (digit >= 'a') digit -= 87;
      else digit -= '0';
      result += digit*pow(16,count);
      count++;
    }//end for
    return result;
  }//end condition
}//end toInt

#endif

//This is a way to handle mathematics with strings, binary strings, integers, or other Hexs.
//At the moment, all that are supported are =, +, and +=. others wil be added as need arises.
class Hex {
  public:
    int value;
    
    Hex();
    Hex(int value);
    Hex(string value);
    Hex(Hex value);
    
    operator+(int add);
    operator+(string add);
    operator+(Hex add);
    
    operator=(int get);
    operator=(string get);
    operator=(Hex get);
    
    operator+=(int add);
    operator+=(string add);
    operator+=(Hex add);
};

Hex::Hex(){
  value = 0;
}

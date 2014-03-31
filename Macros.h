#ifndef MACROSINCLUDED
#define MACROSINCLUDED
#include <map>
#include <string>

namespace macros {
  
class Macro;
std::map<std::string,int> DB;
void initDB();
Macro get(std::string keyword);

}//end namespace
#endif

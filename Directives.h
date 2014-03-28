#ifndef DIRECTIVES_INCLUDED
#define DIRECTIVES_INCLUDED
#include <string>
#include <map>

namespace directives {
  //Keyword will map to an integer referring to 1+ how many arguments the directive takes.  1+ is necessary so 0 can be "does not include" instead of "no arguments"
  map<std::string,int> DB;
  void initDB();
  int get(std::string keyword);
  void process(std::string opor, std::string* opands);


}//end namespace
#endif

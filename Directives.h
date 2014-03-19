#ifndef DIRECTIVES_INCLUDED
#define DIRECTIVES_INCLUDED
#include <string>

std::string directivesDB[?] = {

  };//end array

bool isDirective(std::string keyword){
  for (int i = 0; i < ?; i++){
    if (directivesDB[i] == keyword) return true;
  }//end for
  return false;
}//end get
#endif

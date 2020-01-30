#include <iostream>
#include "fileContainer.hpp"

int main(){
  FileContainer fileController("someDbName");
  std::cout << "Hello, world" << std::endl;
  return 0;
}

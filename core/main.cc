#include <iostream>
#include "fileContainer.hpp"

int main(){
  std::string dbName = "someDbName";
  int totalFragments = 10;
  FileContainer fileController(dbName, totalFragments);
  std::cout << "Hello, world" << std::endl;
  return 0;
}

#include <iostream>
#include "core/fileController.hpp"
#include "core/constants.hpp"

int main(){
  std::string dbName = DRONE_DB_PATH;
  FileController fileController(dbName);
  std::cout << "Hello, world" << std::endl;
  return 0;
}

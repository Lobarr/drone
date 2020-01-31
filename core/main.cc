#include <iostream>
#include <boost/log/trivial.hpp>
#include "core/fileController.hpp"
#include "core/constants.hpp"

int main(){
  std::string dbName = DRONE_DB_PATH;
  std::string filePath = "someFilePath";
  FileController fileController(dbName);
  core::FileRequestPayload fileRequestPayload;
  core::FileFragment fileFragment;
  fileRequestPayload.set_filepath(filePath);
  fileRequestPayload.set_totalfragments(1);
  fileFragment.set_filepath(filePath);
  fileFragment.set_fragmentcontent("justabunchofbytes");
  fileFragment.set_fragmentid(0);
  fileController.createFileContainer(fileRequestPayload);
  fileController.putFileFragment(fileFragment);
  std::cout << "Hello, world" << std::endl;
  return 0;
}

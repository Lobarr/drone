#include "fileController.hpp"


FileController::FileController(const std::string& dbFileName) {
  std::cout << "inside file controller" << std::endl;
  GoString dbFileNameGo = { 
    dbFileName.c_str(), 
    static_cast<ptrdiff_t>(dbFileName.size()) 
  };
  GoInt32 status = createDBService(dbFileNameGo);
  if (status != DBStatus::OK) {
    std::cerr << "Unable to create db service" << std::endl;
  }
}


FileController::~FileController() {
  GoUint8 status = closeDBService();
  if (status != DBStatus::OK) {
    std::cerr << "Unable to close db service" << std::endl;
  }
}


bool FileController::fileExists(const std::string& fileName) {
  std::ifstream f(fileName);
  return f.good();
}



void FileController::assembleFile(const std::string& fileName) {
  if (filesMap.find(fileName) == filesMap.end()) {
    std::cerr << "Unable to assemble invalid file" << std::endl;
    return;
  }

  FileContainer fileContainer = filesMap.at(fileName);
  std::vector<std::string>::iterator fileFragmentsIterator;
  std::ofstream file(
    fileContainer.getFileName(),
    std::ios::out | std::ios::binary
  );
  if (!file.is_open()) {
    std::cerr << "unable to open file" << std::endl;
    return;
  }

  for (
    fileFragmentsIterator = fileContainer.getFragments().begin();
    fileFragmentsIterator != fileContainer.getFragments().end();
    fileFragmentsIterator++
  ) {
    GoString fileFramentIDGo = {(*fileFragmentsIterator), static_cast<ptrdiff_t>((*fileFragmentsIterator).size())};
    getFileFragment_return getFileFragmentReturn = getFileFragment(fileFramentIDGo);
    
  }
}

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

void FileController::putFileFragment(const std::string& fileName, const core::FileFragment& filefragment) {
  boost::uuids::random_generator generator;
  boost::uuids::uuid fileFragmentID = generator();
  std::stringstream fileFragmentIDStringStream;
  // fileFragmentIDStringStream << fileFragmentID;
  // std::
}

void FileController::putFileFragment(const std::string& fileName, const core::FileRequestPayload& fileRequestPayload) {
  if (!inMap(fileName)) {
    filesMap.insert(std::pair<std::string, FileContainer>(fileName, FileContainer(fileName, fileRequestPayload.totalfragments())));
  } else {
    std::cout << "File already being received" << std::endl;
  }
}


void FileController::assembleFile(const std::string& fileName) {
  if (!inMap(fileName)) {
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
    GoString fileFramentIDGo = {(*fileFragmentsIterator).c_str(), static_cast<ptrdiff_t>((*fileFragmentsIterator).size())};
    getFileFragment_return getFileFragmentReturn = getFileFragment(fileFramentIDGo);
    std::tuple<std::string, int> filefragmentReturnTuple = fromFileFragmentReturn(getFileFragmentReturn);
    if (std::get<1>(filefragmentReturnTuple) != DBStatus::OK) {
      std::cerr << "unable to get file fragment" << std::endl;
      return;
    }

    core::FileFragment* fileFragment = deserializeFileFragment(std::get<0>(filefragmentReturnTuple));
    file << fileFragment->fragmentcontent();
  }

  file.close();
}


std::tuple<std::string, int> FileController::fromFileFragmentReturn(const getFileFragment_return& getFileFragmentReturn) const {
  std::tuple<std::string, int> fileFragmentReturnTuple;
  std::string fileFragmentBytes = static_cast<std::string>(getFileFragmentReturn.r0.p);
  int status = getFileFragmentReturn.r1;
  fileFragmentReturnTuple = std::make_tuple(fileFragmentBytes, status);
  return fileFragmentReturnTuple;
}

bool FileController::inMap(const std::string& fileName) {
  if (filesMap.find(fileName) == filesMap.end()) {
    return false;
  }
  return true;
}


#include "fileController.hpp"


FileController::FileController(const std::string& dbFileName) {
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


bool FileController::fileExists(const std::string& filePath) {
  std::ifstream f(filePath);
  return f.good();
}


void FileController::putFileFragment(const core::FileFragment& fileFragment) {
  try {
    std::lock_guard<std::mutex> lockGuard(mutex);

    std::future<std::string*> serializeFileFragmentResult = std::async(std::launch::async, serializeFileFragment, fileFragment);
    boost::uuids::random_generator generator;
    boost::uuids::uuid fileFragmentID = generator();
    std::string fileFragmentIDString = boost::uuids::to_string(fileFragmentID);
    FileContainer fileContainer = filesMap.at(fileFragment.filepath());
    std::string* fileFragmentBytes = serializeFileFragmentResult.get();
    GoString fileFragmentIDGo = {
      fileFragmentIDString.c_str(),
      static_cast<ptrdiff_t>(fileFragmentIDString.size())
    };
    GoString fileFragmentBytesGo = {
      fileFragmentBytes->c_str(),
      static_cast<ptrdiff_t>(fileFragmentBytes->size())
    };

    int status = putFileFragmentInDB(fileFragmentIDGo, fileFragmentBytesGo);
    if (status != DBStatus::OK) {
      throw "Unable to write fileFragment to db";
      return;
    }

    fileContainer.addFragment(fileFragmentIDString);
    filesMap[fileContainer.getFilePath()] = fileContainer;
    if (fileContainer.isComplete()) {
      std::async(std::launch::async, [this, fileContainer](){
        assembleFile(fileContainer.getFilePath());
      });
    }
  } catch(std::string err) {
    std::cerr << err << std::endl;
  }
}


void FileController::createFileContainer(const core::FileRequestPayload& fileRequestPayload) {
  std::lock_guard<std::mutex> lockGuard(mutex);

  if (!inMap(fileRequestPayload.filepath())) {
    std::string filePath = fileRequestPayload.filepath();
    int totalFragments = fileRequestPayload.totalfragments();
    FileContainer fileContainer(filePath, totalFragments);

    filesMap.insert(
      std::pair<std::string, FileContainer>(
        filePath, 
        fileContainer
      )
    );

    return;
  }

  std::cerr << "File already being received" << std::endl;
}


void FileController::assembleFile(const std::string& filePath) {
  try {
    std::lock_guard<std::mutex> lockGuard(mutex);

    if (!inMap(filePath)) {
      std::cerr << "Unable to assemble invalid file" << std::endl;
      return;
    }

    FileContainer fileContainer = filesMap.at(filePath);
    std::vector<std::string>::iterator fileFragmentsIterator;
    std::ofstream file(
      fileContainer.getFilePath(),
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
      GoString fileFramentIDGo = {
        (*fileFragmentsIterator).c_str(),
        static_cast<ptrdiff_t>((*fileFragmentsIterator).size())
      };
      getFileFragmentFromDB_return getFileFragmentReturn = getFileFragmentFromDB(fileFramentIDGo);
      std::tuple<std::string, int> filefragmentReturnTuple = fromFileFragmentReturn(getFileFragmentReturn);
      if (std::get<1>(filefragmentReturnTuple) != DBStatus::OK) {
        std::cerr << "unable to get file fragment" << std::endl;
        return;
      }

      core::FileFragment* fileFragment = deserializeFileFragment(std::get<0>(filefragmentReturnTuple));
      file << fileFragment->fragmentcontent();
    }

    file.close();
    filesMap.erase(filePath);
  } catch(std::string err) {
    std::cerr << err << std::endl;
  }
}


std::tuple<std::string, int> FileController::fromFileFragmentReturn(const getFileFragmentFromDB_return& getFileFragmentReturn) const {
  std::tuple<std::string, int> fileFragmentReturnTuple;
  std::string fileFragmentBytes = static_cast<std::string>(getFileFragmentReturn.r0.p);
  int status = getFileFragmentReturn.r1;
  fileFragmentReturnTuple = std::make_tuple(fileFragmentBytes, status);
  return fileFragmentReturnTuple;
}


bool FileController::inMap(const std::string& filePath) {
  std::lock_guard<std::mutex> lockGuard(mutex);

  if (filesMap.find(filePath) == filesMap.end()) {
    return false;
  }
  return true;
}


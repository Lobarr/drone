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
    mutex.lock();
    boost::uuids::random_generator generator;
    boost::uuids::uuid fileFragmentID = generator();
    std::string fileFragmentIDString = boost::uuids::to_string(fileFragmentID);
    std::string* fileFragmentBytes = serializeFileFragment(fileFragment);
    FileContainer fileContainer = filesMap.at(fileFragment.filepath());
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
      std::cerr << "Unable to write fileFragment to db" << std::endl;
    }

    fileContainer.addFragment(fileFragmentIDString);
    filesMap[fileContainer.getFilePath()] = fileContainer;
    if (fileContainer.isComplete()) {
      boost::thread fileAssemblyThread(&FileController::assembleFile, this, fileContainer.getFilePath());
      fileAssemblyThread.join();
    }
    mutex.unlock();
  } catch(std::string err) {
    std::cerr << err << std::endl;
  }
}


void FileController::createFileContainer(const core::FileRequestPayload& fileRequestPayload) {
  if (!inMap(fileRequestPayload.filepath())) {
    std::string filePath = fileRequestPayload.filepath();
    int totalFragments = fileRequestPayload.totalfragments();
    FileContainer fileContainer(filePath, totalFragments);

    mutex.lock();
    filesMap.insert(
      std::pair<std::string, FileContainer>(
        filePath, 
        fileContainer
      )
    );

    mutex.unlock();
    return;
  }

  std::cerr << "File already being received" << std::endl;
}


void FileController::assembleFile(const std::string& filePath) {
  try {
    if (!inMap(filePath)) {
      std::cerr << "Unable to assemble invalid file" << std::endl;
      return;
    }

    mutex.lock();
    FileContainer fileContainer = filesMap.at(filePath);
    std::vector<std::string>::iterator fileFragmentsIterator;
    std::ofstream file(
      fileContainer.getFilePath(),
      std::ios::out | std::ios::binary
    );
    if (!file.is_open()) {
      std::cerr << "unable to open file" << std::endl;
      mutex.unlock();
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
        mutex.unlock();
        return;
      }

      core::FileFragment* fileFragment = deserializeFileFragment(std::get<0>(filefragmentReturnTuple));
      file << fileFragment->fragmentcontent();
    }

    file.close();
    filesMap.erase(filePath);
    mutex.unlock();
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
  mutex.lock();
  if (filesMap.find(filePath) == filesMap.end()) {
    mutex.unlock();
    return false;
  }
  mutex.unlock();
  return true;
}


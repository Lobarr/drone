#include "fileController.hpp"


FileController::FileController(const std::string& dbFileName) {
  std::cout << "[FileController] Initalizing fileController" << std::endl;

  GoString dbFileNameGo = { 
    dbFileName.c_str(), 
    static_cast<ptrdiff_t>(dbFileName.size()) 
  };
  GoInt32 status = createDBService(dbFileNameGo);
  if (status != DBStatus::OK) {
    std::cerr << "Unable to create db service" << std::endl;
    exit(1);
  }
}


FileController::~FileController() {
  std::cout << "[FileController] Cleaning up fileController" << std::endl;

  GoUint8 status = closeDBService();
  if (status != DBStatus::OK) {
    std::cerr << "[FileController] Unable to close db service" << std::endl;
  }
  exit(1);
}


bool FileController::fileExists(const std::string& filePath) {
  std::ifstream f(filePath);
  return f.good();
}


void FileController::putFileFragment(const core::FileFragment& fileFragment) {
  std::cout << "[FileController] Putting fileFragment " << fileFragment.fragmentid() << " of file " << fileFragment.filepath() << std::endl;

  std::lock_guard<std::mutex> lockGuard(mutex);

  if (inMap(fileFragment.filepath()) == false) {
    createFileContainer(fileFragment);
  }

  std::string* fileFragmentBytes = NULL;
  std::future<void> serializeFileFragmentAsync = std::async(std::launch::async, serializeFileFragment, fileFragment, fileFragmentBytes);
  boost::uuids::random_generator generator;
  boost::uuids::uuid fileFragmentID = generator();
  std::string fileFragmentIDString = boost::uuids::to_string(fileFragmentID);
  serializeFileFragmentAsync.get();
  FileContainer fileContainer = filesMap.at(fileFragment.filepath());
  serializeFileFragmentAsync.get();
  
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
    std::cerr << "[FileController] Unable to write fileFragment to db" << std::endl;
    return;
  }

  fileContainer.addFragment(fileFragmentIDString);
  filesMap[fileContainer.getFilePath()] = fileContainer;
  if (fileContainer.isComplete()) {
    std::async(std::launch::async, [this, fileContainer](){
      assembleFile(fileContainer.getFilePath());
    });
  }
}


void FileController::createFileContainer(const core::FileFragment& fileFragment) {
  std::cout << "[FileController] Initalizing receipt of " << fileFragment.filepath() << std::endl;

  std::string filePath = fileFragment.filepath();
  int totalFragments = fileFragment.totalfragments();
  FileContainer fileContainer(filePath, totalFragments);

  filesMap.insert(
    std::pair<std::string, FileContainer>(
      filePath, 
      fileContainer
    )
  );

  return;
}


void FileController::assembleFile(const std::string& filePath) {
  try {
    std::lock_guard<std::mutex> lockGuard(mutex);

    if (!inMap(filePath)) {
      std::cerr << "[FileController] Unable to assemble invalid file" << std::endl;
      return;
    }

    FileContainer fileContainer = filesMap.at(filePath);
    std::vector<std::string>::iterator fileFragmentsIterator;
    std::ofstream file(
      fileContainer.getFilePath(),
      std::ios::out | std::ios::binary
    );
    if (!file.is_open()) {
      std::cerr << "[FileController] Unable to open file" << std::endl;
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
        std::cerr << "[FileController] Unable to get file fragment" << std::endl;
        return;
      }

      core::FileFragment* fileFragment = NULL;
      deserializeFileFragment(std::get<0>(filefragmentReturnTuple), fileFragment);
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
  if (filesMap.find(filePath) == filesMap.end()) {
    return false;
  }
  return true;
}

void FileController::handleFileRequest(const core::FileRequestPayload& fileRequestPayload) {
  std::cout << "[FileController] Handling file request" << std::endl;
}

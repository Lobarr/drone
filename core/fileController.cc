#include "fileController.hpp"


FileController::FileController(const std::string& dbFileName) {
  DBService _dbService(dbFileName);
  dbService = _dbService;
}


FileController::~FileController() {}


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

  std::future<std::string> serializeFileFragmentAsync = std::async(std::launch::async, serializeFileFragment, fileFragment);
  boost::uuids::random_generator generator;
  boost::uuids::uuid fileFragmentID = generator();
  std::string fileFragmentIDString = boost::uuids::to_string(fileFragmentID);
  FileContainer fileContainer = filesMap.at(fileFragment.filepath());
  std::string fileFragmentBytes = serializeFileFragmentAsync.get();

  dbService.putFileFragment(fileFragmentIDString, fileFragmentBytes);
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
    std::cout << "[FileController] Assembling file " << filePath << std::endl;

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
      std::string fileFragmentBytes;
      dbService.getFileFragment(*fileFragmentsIterator, fileFragmentBytes);

      core::FileFragment fileFragment = deserializeFileFragment(fileFragmentBytes);
      file << fileFragment.fragmentcontent();
    }

    file.close();
    filesMap.erase(filePath);
  } catch(std::string err) {
    std::cerr << err << std::endl;
  }
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

#include "fileController.hpp"

FileController::FileController(DBService* dbService) : dbService(dbService) {}
FileController::~FileController() {}

bool FileController::fileExists(const std::string& fileName) {
  std::ifstream f(fileName);
  return f.good();
}

// void FileController::fragmentizeFile(std::string* fileName) {

// };


// void FileController::assembleFileFragments(std::vector<core::FileFragment>* fileFragments) {

// };



#include "fileController.hpp"


FileController::FileController(const std::string& dbFileName) {
  GoString dbFileNameGo = { dbFileName.c_str(), dbFileName.size() };
  GoInt32 status = CreateDBService(dbFileNameGo);
  if (status != DBStatus::OK) {
    std::cerr << "Unable to create db service" << std::endl;
  }
}


FileController::~FileController() {
  GoUint8 status = CloseDBService();
  bool ok = (bool)status;
  if (!ok) {
    std::cerr << "Unable to close db service" << std::endl;
  }
}

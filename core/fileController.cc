#include "fileController.hpp"


FileController::FileController(const std::string& dbFileName) {
  std::cout << "inside file controller" << std::endl;
  GoString dbFileNameGo = { dbFileName.c_str(), static_cast<ptrdiff_t>(dbFileName.size()) };
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

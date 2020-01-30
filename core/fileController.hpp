#ifndef FILE_CONTROLLER_HPP
#define FILE_CONTROLLER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "core/drone.pb.h"
#include "services/db/drone_db_service.h"
#include "fileContainer.hpp"


enum DBStatus {
  OK = 0,
  NOT_OK = 1
};

class FileController {
  public:
    FileController(const std::string& dbFileName);
    ~FileController();
    bool fileExists(const std::string& fileName);
    void putFileFragment(const std::string& fileName, const core::FileFragment& fileFragment);
    void assembleFile(const std::string& fileName);
  private:
    std::map<std::string, FileContainer> filesMap; // fileName -> fileContainer
};

#endif

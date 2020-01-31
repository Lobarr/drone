#ifndef FILE_CONTROLLER_HPP
#define FILE_CONTROLLER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "core/drone.pb.h"
#include  "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid.hpp"
#include "services/db/drone_db_service.h"
#include "fileContainer.hpp"
#include "serializeUtil.hpp"


enum DBStatus {
  OK = 0,
  NOT_OK = 1
};

class FileController {
  public:
    FileController(const std::string& dbfilePath);
    ~FileController();
    bool fileExists(const std::string& filePath);
    void putFileFragment(const std::string& filePath, const core::FileFragment& fileFragment);
    void putFileFragment(const std::string& filePath, const core::FileRequestPayload& fileRequestPayload);
    void assembleFile(const std::string& filePath);
    bool inMap(const std::string& filePath);
    std::tuple<std::string, int> fromFileFragmentReturn(const getFileFragment_return& getFileFragmentReturn) const;
  private:
    std::map<std::string, FileContainer> filesMap; // filePath -> fileContainer
};

#endif

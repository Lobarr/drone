#ifndef FILE_CONTROLLER_HPP
#define FILE_CONTROLLER_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>
#include <string>
#include "boost/lexical_cast.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid.hpp"
#include "core/drone.pb.h"
#include "fileContainer.hpp"
#include "serializeUtil.hpp"
#include "services/db/drone_db_service.h"


enum DBStatus {
  OK = 0,
  NOT_OK = 1
};

class FileController {
  public:
    FileController(const std::string& dbfilePath);
    ~FileController();
    bool fileExists(const std::string& filePath);
    void putFileFragment(const core::FileFragment& fileFragment);
    void createFileContainer(const core::FileRequestPayload& fileRequestPayload);
    void assembleFile(const std::string& filePath);
    bool inMap(const std::string& filePath);
    std::tuple<std::string, int> fromFileFragmentReturn(const getFileFragmentFromDB_return& getFileFragmentReturn) const;
  private:
    std::map<std::string, FileContainer> filesMap; // filePath -> fileContainer
    std::mutex mutex;
};

#endif

#ifndef FILE_CONTROLLER_HPP
#define FILE_CONTROLLER_HPP

#include "core/drone_db_service.h"
#include "core/drone.pb.h"
#include "fileContainer.hpp"
#include "serializeUtil.hpp"
#include <boost/log/trivial.hpp>
#include <boost/thread/thread.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <fstream>
#include <future>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>


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
    void createFileContainer(const core::FileFragment& fileFragment);
    void assembleFile(const std::string& filePath);
    bool inMap(const std::string& filePath);
    void handleFileRequest(const core::FileRequestPayload& fileRequestPayload);
    std::tuple<std::string, int> fromFileFragmentReturn(const getFileFragmentFromDB_return& getFileFragmentReturn) const;
  private:
    std::map<std::string, FileContainer> filesMap; // filePath -> fileContainer
    std::mutex mutex;
};

#endif

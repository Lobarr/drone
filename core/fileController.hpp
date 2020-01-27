#ifndef FILE_CONTROLLER_HPP
#define FILE_CONTROLLER_HPP

#include "core/drone.pb.h"
#include "leveldb/db.h"
#include "dbService.cc"
#include <string>
#include <vector>
#include <fstream>


class FileController {
  public:
    FileController(DBService* dbService);
    ~FileController();
    void fragmentizeFile(const std::string* fileName);
    void assembleFileFragments(const std::vector<core::FileFragment>* fileFragments);
    bool fileExists(const std::string& fileName);
  private:
    DBService* dbService;
};

#endif

#ifndef DB_SERVICE_HPP
#define DB_SERVICE_HPP

#include "core/drone.pb.h"
#include "leveldb/db.h"
#include <vector>

class DBService {
  public:
    DBService();
    ~DBService();
    void initDatabase();
    void putFileFragment(const std::string& fileName, const core::FileFragment& fileFragment);
    void putFileFragments(const std::string& fileName, const std::vector<core::FileFragment>& fileFragments);
    std::vector<core::FileFragment>* getFileFragments(std::string& fileName) const;

  private:
    leveldb::DB* db;
};

#endif

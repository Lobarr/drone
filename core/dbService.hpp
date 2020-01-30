#ifndef DB_SERVICE_HPP
#define DB_SERVICE_HPP

#include "core/drone.pb.h"
#include "rocksdb/db.h"
#include <vector>

class DBService {
  public:
    DBService();
    ~DBService();
    void initDatabase();
    std::string* putFileFragment(const std::string& fileName, const core::FileFragment& fileFragment);
    core::FileFragment* getFileFragment(const std::string& id);
    core::FileFragment* fromMsgPack(const msgpack::sbuffer& buffer);
    msgpack::sbuffer* toMsgPack(const core::FileFragment& fileFragment);
    std::string* serializeFileFragment(const core::FileFragment& fileFragment);
    core::FileFragment* deserializeFileFragment(std::string& fileFragmentBytes);
  private:
    rocksdb::DB* db;
};

#endif

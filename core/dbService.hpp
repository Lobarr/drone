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
    void putFileFragment(const std::string& fileName, core::FileFragment& fileFragment);
    void putFileFragments(const std::string& fileName, const std::vector<core::FileFragment*> fileFragments);
    std::vector<core::FileFragments> getFileFragments(std::string& fileName) const;
    msgpack::sbuffer* toMsgPack(const std::vector<core::FileFragment*>& fileFragments);
    std::vector<core::FileFragment*>* fromMsgPack(const msgpack::sbuffer& buffer);
    std::vector<std::string> fileFragmentsToBytes(const std::vector<core::FileFragment*>& fileFragments);
    std::vector<core::FileFragment*>* bytesToFileFragments(std::vector<std::string> fileFragmentBytes);
  private:
    rocksdb::DB* db;
};

#endif

#ifndef DB_SERVICE_HPP
#define DB_SERVICE_HPP

#include <string>
#include "leveldb/db.h"

class DBService {
  public:
    DBService();
    DBService(const std::string& dbFileName);
    ~DBService();
    void putFileFragment(const std::string& fragmentID, std::string& fileFragmentBytes);
    void getFileFragment(const std::string& fragmentID, std::string& fileFragmentBytes);
    void removeFileFragments(const std::vector<std::string> fileFragmentIDs);
  private:
    leveldb::DB* db;
};


#endif

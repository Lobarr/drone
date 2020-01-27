#include "dbService.hpp"

DBService::DBService() {
  initDatabase();
};

DBService::~DBService() {
  delete db;
};

void DBService::initDatabase() {
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/dronedb", &db);
  assert(status.ok());
}

void DBService::putFileFragment(const std::string& fileName, const core::FileFragment& fileFragment) {
  
}

void DBService::putFileFragments(const std::string& fileName, const std::vector<core::FileFragment>& fileFragments) {

}

std::vector<core::FileFragment>* DBService::getFileFragments(std::string& fileName) const {
  std::vector<core::FileFragment>* fileFragments;
  leveldb::Status dbStatus = db->Get(leveldb::ReadOptions(), fileName, &fileName);
}

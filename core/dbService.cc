#include "core/dbService.hpp"
DBService::DBService() {}

DBService::DBService(const std::string& dbFileName) {
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, dbFileName, &db);
  assert(status.ok());
}

DBService::~DBService() {
  delete db;
}

void DBService::putFileFragment(const std::string& fragmentID, std::string& fileFragmentBytes) {
  leveldb::Status status = db->Put(leveldb::WriteOptions(), fragmentID, fileFragmentBytes);
  if (!status.ok()) throw "[DBService] Unable to write fileFragment to DB";
}

void DBService::getFileFragment(const std::string& fragmentID, std::string& fileFragmentBytes) {
  leveldb::Status status = db->Get(leveldb::ReadOptions(), fragmentID, &fileFragmentBytes);
  if (!status.ok()) throw "[DBService] Unable to get fileFragment from DB";
}

void DBService::removeFileFragments(const std::vector<std::string> fileFragmentIDs) {
  // leveldb::Status status;
  // leveldb::WriteBatch batch;
  // std::vector<std::string>::const_iterator fileFragmentIDsIterator;

  // for (
  //   fileFragmentIDsIterator = fileFragmentIDs.begin();
  //   fileFragmentIDsIterator != fileFragmentIDs.end();
  //   fileFragmentIDsIterator++
  // ) {
  //   batch.Delete(*fileFragmentIDsIterator);
  // }

  // status = db->Write(leveldb::WriteOptions(), &batch);
  // if (!status.ok()) throw "[DBService] Unable to remove file fragments from DB";
}

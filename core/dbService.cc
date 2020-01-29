#include "dbService.hpp"
#include "msgpack.hpp"

DBService::DBService() {
  initDatabase();
};

DBService::~DBService() {
  delete db;
};

void DBService::initDatabase() {
  rocksdb::Options options;
  options.create_if_missing = true;
  rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/dronedb", &db);
  assert(status.ok());
}

void DBService::putFileFragment(const std::string& fileName, core::FileFragment& fileFragment) {
  std::vector<core::FileFragment&> fileFragments;
  std::string* fileFragmentsBytes;
  std::string* fileBytes;
  
  bool ok = fileFragment.SerializeToString(fileBytes);
  if (!ok) throw "Unable to serialize fileFragment";
  
  rocksdb::Status status = db->Get(rocksdb::ReadOptions(), fileName, fileFragmentsBytes);
  if (status.IsNotFound()) {
    fileFragments.push_back(fileFragment);
  } else {
    // fileFragments = fromMsgPack()
  }
}

// void DBService::putFileFragments(const std::string& fileName, const std::vector<core::FileFragment>& fileFragments) {

// }

// std::vector<core::FileFragment*> DBService::getFileFragments(std::string& fileName) const {
//   std::vector<core::FileFragment*> fileFragments;
//   rocksdb::Status dbStatus = db->Get(rocksdb::ReadOptions(), fileName, &fileName);
// }

msgpack::sbuffer* DBService::toMsgPack(const std::vector<core::FileFragment*>& fileFragments) {
  std::vector<std::string> fileFragmentBytes = fileFragmentsToBytes(fileFragments);
  msgpack::sbuffer* sBuffer;
  msgpack::pack(sBuffer, fileFragmentsBytes);
  return sBuffer;
}

std::vector<core::FileFragment*>* fromMsgPack(const msgpack::sbuffer& sBuffer) {
  std::vector<std::string> fileFragmentsBytes;
  msgpack::unpacked msg;
  msgpack::object obj;

  msgpack::unpack(&msg, sBuffer.data(), sBuffer.size());
  obj = msg.get();
  obj.convert(&fileFragmentsBytes);

  return bytesToFileFragments(fileFragmentsBytes);
}


std::vector<std::string> DBService::fileFragmentsToBytes(const std::vector<core::FileFragment*>& fileFragments) {
  std::vector<std::string> fileFragmentsBytes;
  std::vector<core::FileFragment*>::iterator fileFragmentsIterator;

  for (fileFragmentsIterator = fileFragments.begin(); fileFragmentsIterator < fileFragments.end(); fileFragmentsIterator++) {
    std::string fileFragmentBytes;
    bool ok = (*fileFragmentsIterator)->SerializeToString(&fileFragmentBytes);
    if (!ok) throw "Unable to serialize fileFragment";
    fileFragmentsBytes.push_back(fileFragmentBytes);
  }

  return fileFragmentsBytes;
}


std::vector<core::FileFragment*>* DBService::bytesToFileFragments(std::vector<std::string> fileFragmentBytes) {
  std::vector<core::FileFragment*>* fileFragments;
  std::vector<std::string>::iterator fileFragmentsBytesIterator;

  for(fileFragmentsBytesIterator = fileFragmentsBytes.begin(); fileFragmentsBytesIterator < fileFragmentsBytes.end(); fileFragmentsBytesIterator++) {
    core::FileFragment* fileFragment;
    bool ok = fileFragment->ParseFromString(*fileFragmentsBytesIterator)
    if (!ok) throw "Unable to deserialize fileFragment";
    fileFragments.push_back(fileFragment);
  }

  return fileFragments;
}

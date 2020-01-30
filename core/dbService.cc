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
  rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/dronedb", db);
  assert(status.ok());
}

std::string* DBService::putFileFragment(const std::string& fileName, const core::FileFragment& fileFragment) {
  rocksdb::Status status = db->Get(rocksdb::ReadOptions(), fileName, serializeFileFragment(fileFragment));
  // generate uuid
  if (status.IsNotFound()) {
    fileFragments.push_back(fileFragment);
  } else {  
    // fileFragments = fromMsgPack()
  }
}

// std::vector<core::FileFragment*> DBService::getFileFragments(std::string& fileName) const {
//   std::vector<core::FileFragment*> fileFragments;
//   rocksdb::Status dbStatus = db->Get(rocksdb::ReadOptions(), fileName, &fileName);
// }

msgpack::sbuffer* DBService::toMsgPack(const core::FileFragment& fileFragment) {
  std::string fileFragmentBytes = fileFragmentToBytes(fileFragment);
  msgpack::sbuffer* sBuffer;
  
  msgpack::pack(sBuffer, fileFragmentsBytes);

  return sBuffer;
}

core::FileFragment* fromMsgPack(const msgpack::sbuffer& sBuffer) {
  std::string* fileFragmentBytes;
  msgpack::unpacked* msg;
  msgpack::object* obj;

  msgpack::unpack(msg, sBuffer.data(), sBuffer.size());
  obj = msg->get();
  obj->convert(fileFragmentBytes);

  return deseralizeFileFragment(fileFragmentBytes);
}


std::string* DBService::serializeFileFragment(const core::FileFragment& fileFragment) {
  std::string* fileFragmentsBytes;
  bool ok = fileFragment.SerializeToString(fileFragmentBytes);

  if (!ok) throw "Unable to serialize fileFragment";

  return fileFragmentsBytes;
}


core::FileFragment* DBService::deserializeFileFragment(std::string& fileFragmentBytes) {
  core::FileFragment* fileFragment;
  bool ok = fileFragment->ParseFromString(fileFragmentBytes);

  if (!ok) throw "Unable to deserialize fileFragment";

  return fileFragment;
}

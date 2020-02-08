#include "serializeUtil.hpp"

std::string serializeFileFragment(const core::FileFragment& fileFragment) {
  std::string fileFragmentBytes;
  bool ok = fileFragment.SerializeToString(&fileFragmentBytes);  
  if (!ok) throw "Unable to serialize fileFragment";
  return fileFragmentBytes;
}


core::FileFragment deserializeFileFragment(std::string& fileFragmentBytes) {
  core::FileFragment fileFragment;
  bool ok = fileFragment.ParseFromString(fileFragmentBytes);
  if (!ok) throw "Unable to deserialize fileFragment";
  return  fileFragment;
}

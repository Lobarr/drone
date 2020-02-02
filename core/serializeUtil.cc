#include "serializeUtil.hpp"

void serializeFileFragment(const core::FileFragment& fileFragment, std::string* fileFragmentBytes) {
  bool ok = fileFragment.SerializeToString(fileFragmentBytes);  
  if (!ok) throw "Unable to serialize fileFragment";
}


void deserializeFileFragment(std::string& fileFragmentBytes, core::FileFragment* fileFragment) {
  bool ok = fileFragment->ParseFromString(fileFragmentBytes);
  if (!ok) throw "Unable to deserialize fileFragment";
}

#ifndef SERIALIZE_UTIL_HPP
#define SERIALIZE_UTIL_HPP

#include "google/protobuf/message.h"
#include "core/drone.pb.h"

void serializeFileFragment(const core::FileFragment& fileFragment, std::string* fileFragmentBytes);
void deserializeFileFragment(std::string& fileFragmentBytes, core::FileFragment* fileFragment);

#endif

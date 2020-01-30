#ifndef SERIALIZE_UTIL_HPP
#define SERIALIZE_UTIL_HPP

#include "core/drone.pb.h"

std::string* serializeFileFragment(const core::FileFragment& fileFragment);
core::FileFragment* deserializeFileFragment(std::string& fileFragmentBytes);

#endif

#pragma once

#include "core/drone.pb.h"
#include <string>
#include <vector>

class FileController {
  public:
    static void getFileFragments(std::string* fileName);
    static void makeFileFromFragments(std::vector<core::FileFragment>* fileFragments);
};

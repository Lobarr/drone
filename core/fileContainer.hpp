#ifndef FILE_CONTAINER_HPP
#define FILE_COINTAINER_HPP

#include "drone.pb.h"
#include <vector>

class FileContainer {
  public:
    FileContainer(const std::string& fileName);
    ~FileContainer();
    void addFragment(const std::string& fragmentKey);
    std::vector<std::string> getFragments() const;
  private:
    std::string fileName;
    std::vector<std::string> fragmentKeys;
};


#endif

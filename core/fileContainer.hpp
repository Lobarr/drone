#ifndef FILE_CONTAINER_HPP
#define FILE_COINTAINER_HPP

#include <vector>
#include "core/drone.pb.h"


class FileContainer {
  public:
    FileContainer(const std::string& fileName, const int& totalFragments);
    ~FileContainer();
    void addFragment(const std::string& fragmentKey);
    std::vector<std::string> getFragments() const;
    bool isComplete() const;
  private:
    std::string fileName;
    std::vector<std::string> fragmentKeys;
    int totalFragments;
};


#endif

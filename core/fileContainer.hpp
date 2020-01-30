#ifndef FILE_CONTAINER_HPP
#define FILE_CONTAINER_HPP

#include <vector>
#include "core/drone.pb.h"


class FileContainer {
  public:
    FileContainer(const std::string& fileName, const int& totalFragments);
    ~FileContainer();
    void addFragment(const std::string& fragmentKey);
    std::vector<std::string> getFragments() const;
    bool isComplete() const;
    std::string getFileName() const;
    std::tuple<std::string, int> fromFileFragmentReturn(getFileFragment_return getFileFragmentReturn);
  private:
    std::string fileName;
    std::vector<std::string> fragmentKeys;
    int totalFragments;
};


#endif

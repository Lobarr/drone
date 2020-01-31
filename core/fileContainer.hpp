#ifndef FILE_CONTAINER_HPP
#define FILE_CONTAINER_HPP

#include <vector>
#include "core/drone.pb.h"


class FileContainer {
  public:
    FileContainer();
    FileContainer(std::string& filePath, int& totalFragments);
    ~FileContainer();
    void addFragment(const std::string& fragmentKey);
    std::vector<std::string> getFragments() const;
    bool isComplete() const;
    std::string getFilePath() const;
  private:
    std::string filePath;
    std::vector<std::string> fragmentKeys;
    int totalFragments;
};


#endif

#include "fileContainer.hpp"

FileContainer::FileContainer(const std::string& fileName, const int& totalFragments)
:fileName(fileName), totalFragments(totalFragments) {};

FileContainer::~FileContainer() {};

void FileContainer::addFragment(const std::string& fragmentKey) {
  fragmentKeys.push_back(fragmentKey);
};

std::vector<std::string> FileContainer::getFragments() const {
  return fragmentKeys;
}

bool FileContainer::isComplete() const {
  return fragmentKeys.size() == static_cast<unsigned int>(totalFragments);
}

std::string FileContainer::getFileName() const {
  return fileName;
}

std::tuple<std::string, int> FileContainer::fromFileFragmentReturn(getFileFragment_return getFileFragmentReturn) {

}


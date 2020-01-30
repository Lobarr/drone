#include "fileContainer.hpp"

FileContainer::FileContainer(const std::string& fileName): fileName(fileName) {};

FileContainer::~FileContainer() {};

void FileContainer::addFragment(const std::string& fragmentKey) {
  fragmentKeys.push_back(fragmentKey);
};

std::vector<std::string> FileContainer::getFragments() const {
  return fragmentKeys;
}


#include "fileContainer.hpp"

FileContainer::FileContainer(std::string& filePath, int& totalFragments) {
  filePath = filePath;
  totalFragments = totalFragments;
};

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

std::string FileContainer::getFilePath() const {
  return filePath;
}


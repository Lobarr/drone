#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP


#include <string>
#include <cstdlib>
#include <boost/filesystem.hpp>

boost::filesystem::path makeDronePath() {
  boost::filesystem::path homeDirPath{ std::getenv("HOME") };
  boost::filesystem::path droneDirPath{ ".drone" };
  boost::filesystem::path dronePath = homeDirPath / droneDirPath;
  return  dronePath;
}

boost::filesystem::path makeDroneDBPath() {
  boost::filesystem::path dbDirPath = "/db";
  boost::filesystem::path dbPath = makeDronePath() / dbDirPath;
  return dbPath;
}
const boost::filesystem::path DRONE_DB_PATH = makeDroneDBPath();
const boost::filesystem::path DRONE_PATH = makeDronePath();

#endif

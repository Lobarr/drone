#include "core/constants.hpp"
#include "core/fileController.hpp"
#include "core/droneService.hpp"
#include <boost/log/trivial.hpp>
#include <iostream>

void startServer(FileController& fileController) {
  std::string serverAddr = "0.0.0.0:9999";
  DroneServiceImpl droneService(fileController);
  grpc::ServerBuilder serverBuilder;

  serverBuilder.AddListeningPort(serverAddr, grpc::InsecureServerCredentials());
  serverBuilder.RegisterService(&droneService);
  std::unique_ptr<grpc::Server> server(serverBuilder.BuildAndStart());
  std::cout << "[Drone] Starting on " << serverAddr << std::endl;
  server->Wait();
}

int main(){
  std::string dbName = DRONE_DB_PATH;
  std::string filePath = "someFilePath";
  FileController fileController(filePath);
  startServer(fileController);
  return 0;
}

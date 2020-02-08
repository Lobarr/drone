#include "core/constants.hpp"
#include "core/fileController.hpp"
#include "core/droneService.hpp"
#include "core/dbService.hpp"
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
  FileController fileController(DRONE_DB_PATH.string());
  startServer(fileController);
  return 0;
}

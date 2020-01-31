#include "core/drone.pb.h"
#include "core/drone.grpc.pb.h"
#include "core/fileController.hpp"


class DroneServiceImpl final : public core::Drone::Service {
  public:
    grpc::Status ReceiveFile(
      grpc::ServerContext& context, 
      grpc::ServerReader<core::FileFragment>& serverReader, 
      core::Status& status
    ) {
      
      return grpc::Status::OK;
    };


    grpc::Status SendFiles(
      grpc::ServerContext& context,
      const core::FileRequest& fileRequest,
      core::Status& status
    ) {
      
      return grpc::Status::OK;
    }

  private:
    FileController fileController;
};

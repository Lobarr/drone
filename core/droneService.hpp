#include "core/drone.grpc.pb.h"
#include "core/drone.pb.h"
#include "core/fileController.hpp"
#include "grpcpp/grpcpp.h"
#include <memory>


class DroneServiceImpl final : public core::Drone::Service {
  public:

    explicit DroneServiceImpl(FileController& fc) {
      fileController = &fc;
    }

    grpc::Status ReceiveFile(
      grpc::ServerContext* context, 
      grpc::ServerReader<core::FileFragment>* serverReader, 
      core::Status* status
    ) {

      core::FileFragment filefRagmentBuffer;
      while(serverReader->Read(&filefRagmentBuffer)) {
        fileController->putFileFragment(filefRagmentBuffer);
        std::cout << "put file fragment" << std::endl;
      }

      return grpc::Status::OK;
    };


    grpc::Status SendFiles(
      grpc::ServerContext* context,
      const core::FileRequest* fileRequest,
      core::Status* status
    ) {

      
      for (
        int fileRequestPayloadIndex = 0;
        fileRequestPayloadIndex < fileRequest->filerequestpayloads_size();
        fileRequestPayloadIndex++
      ){
        const core::FileRequestPayload& fileRequestPayload = fileRequest->filerequestpayloads(fileRequestPayloadIndex);
        std::async(std::launch::async, [fileRequestPayload, this](){
          fileController->handleFileRequest(fileRequestPayload);
        });
      }
      
      return grpc::Status::OK;
    }

  private:
    FileController* fileController;
};


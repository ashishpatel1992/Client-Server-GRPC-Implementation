
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>


#include "rpcserv.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status; 
using rpcserv::Call;
using rpcserv::Return;
using rpcserv::AddRPCService;

#define MAX_MSG_SIZE 1024

class AddRPCServiceClient {
 public:
  AddRPCServiceClient(std::shared_ptr<Channel> channel): stub_(AddRPCService::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string AddRPC(const std::string& user, const std::string& data) {
    // Data we are sending to the server.
    Call request;
    // int args_x[] = {5,10};
    request.set_name(user);
    // std::cout<<google::protobuf::serializ(args_x);
    request.set_args(data);
    // std::string test[255];
    // request.SerializeToString(test);
    // std::cout<<test<<"\n";
    // request.ParseFromString(*test);
    // std::cout<<test<<"\n";
    
    // Container for the data we expect from the server.
    Return reply;
    // reply.SerializeToString()
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
  
    // The actual RPC.
    Status status = stub_->AddRPC(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return (reply.message()+" "+reply.value());
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }

    // Call hr = Call_INIT;
  }

 private:
  std::unique_ptr<AddRPCService::Stub> stub_;
};
void help(){
  std::cout<<"\n Only Two actions permitted: \n\t1) add \n\t2) gettotal";
  std::cout<<"\n use ./rpcserv_client add x y\n\t where x and y can be any integer number";
  std::cout<<"\n use ./rpcserv_client gettotal\n\t Returns the total sum computer in Server\n";
}


int main(int argc, char* argv[]) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  // intro();
  AddRPCServiceClient AddRPCService(grpc::CreateChannel("localhost:9999", grpc::InsecureChannelCredentials()));
  if(argc<2){
    std::cout<<"\nInvalid RPC Call ";
    help();
    return 0;
  }
  std::string user;
  user = argv[1];
  std::string args;
  
  for (int i = 2; i < argc; ++i){
        if(user == "add"){
            args = args+argv[i]+" ";
            // cout << argv[i] << "\n"; 
        }else break;
    } 
  
  std::string reply = AddRPCService.AddRPC(user,args);
  if(reply != "")
    if(user == "add")
      std::cout << "Sum received: " << reply <<"\n";
    else if(user == "gettotal")
      std::cout<<" Total is "<< reply<<"\n";
    else  std::cout<<" ";
  return 0;
}

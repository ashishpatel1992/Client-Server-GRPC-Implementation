/**
 *  Description: RPC Client - sends function name and arguments to server
 *  Developed by: Ashish Patel & Nand Parikh
 **/
 
#include <iostream>
#include <string>
#include <arpa/inet.h>

#include <grpcpp/grpcpp.h>
#include "rpcserv.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status; 
using rpcserv::Call;
using rpcserv::Return;
using rpcserv::AddRPCService;

#define MAX_MSG_SIZE 1024
struct rpc_response{
  bool success;
  int32_t value;
};

class AddRPCServiceClient {
  private:
    std::unique_ptr<AddRPCService::Stub> stub_;
  public:
    AddRPCServiceClient(std::shared_ptr<Channel> channel): stub_(AddRPCService::NewStub(channel)) {}

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    rpc_response AddRPC(const std::string& func_name, const std::string& arg_data) {
      // Data we are sending to the server.
      Call request;
      request.set_name(func_name);
      request.set_args(arg_data);
      
      std::string serializedData;
      request.SerializeToString(&serializedData);
      
      // Container for the data we expect from the server.
      Return reply;
      
      // Context for the client. It could be used to convey extra information to
      // the server and/or tweak certain RPC behaviors.
      ClientContext context;
    
      // RPC Call
      Status status = stub_->AddRPC(&context, request, &reply);

      // Action for RCP response
      if (status.ok()) {
        rpc_response rpc_r;
        rpc_r.success = reply.success();
        rpc_r.value = stoi(reply.value());
        return rpc_r;
        // return (reply.message()+" "+reply.value());
      } else {
        rpc_response rpc_r;
        rpc_r.value = -1;
        rpc_r.success = false;
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return rpc_r;
      }
    }


};
void help(){
  std::cout<<"\n Only Two actions permitted: \n\t1) add \n\t2) gettotal";
  std::cout<<"\n use ./rpcserv_client [ip] [port] add x y\n\t where x and y can be any integer number";
  std::cout<<"\n use ./rpcserv_client [ip] [port] gettotal\n\t Returns the total sum computer in Server\n";
}


int main(int argc, char* argv[]) {
  struct in_addr addr;
  
  if(argc<4){
    std::cout<<"\n===================";
    std::cout<<"\nInvalid RPC Call ";
    std::cout<<"\n===================";
    help();
    return 0;
  }
  char* ip_addr = argv[1];
  if(!inet_aton(ip_addr,&addr)){
    std::cout<<"\n Invalid IP address";
    return 0;
  }
  
  std::string port_no = argv[2];
  std::string socket_addr = argv[1];
  socket_addr+=":";
  socket_addr+=argv[2];
  
  AddRPCServiceClient AddRPCService(grpc::CreateChannel(socket_addr, grpc::InsecureChannelCredentials())); 
  std::string func_name;
  
  func_name = argv[3];
  std::string arg_data;
  
  for (int i = 4; i < argc; ++i){
    arg_data = arg_data+argv[i]+" ";
  } 
  
  rpc_response reply = AddRPCService.AddRPC(func_name,arg_data);

  if(reply.success){
    std::cout<<"\nAction: "<<func_name;
    std::cout<<"\nResult: "<<reply.value;
    std::cout<<"\n";
  }else{
    std::cout<<"\nAction: "<<func_name<<" does not exist\n";
    help();
  }

  return 0;
}

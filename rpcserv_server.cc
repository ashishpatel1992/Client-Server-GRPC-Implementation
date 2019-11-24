/**
 *  Description: RPC Client - sends function name and arguments to server
 *  Developed by: Ashish Patel & Nand Parikh
 **/

#include <iostream>
#include <string>
#include <sstream>
#include <arpa/inet.h>

#include <grpcpp/grpcpp.h>
#include "rpcserv.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using rpcserv::Call;
using rpcserv::Return;
using rpcserv::AddRPCService;

static uint32_t total = 0;

uint32_t add(uint32_t a, uint32_t b){
  total+= (a + b);
  return (a+b);
}

uint32_t gettotal(void){
  return (total);
}

void intro(){
  std::cout<<"\n **************************************************";
  std::cout<<"\n *\tDeveloped by: ";
  std::cout<<"\n *\tAshish Patel (2019H1030028G) ";
  std::cout<<"\n *\tNand Parikh  (2019H1030022G) ";
  std::cout<<"\n ***************************************************\n";
}
using namespace std;
// Logic and data behind the server's behavior.
class AddRPCServiceServiceImpl final : public AddRPCService::Service {
  Status AddRPC(ServerContext* context, const Call* request, Return* reply) override {
    
    if(request->name() == "add" || request->name() == "ADD" ){
      
      uint32_t x,y;
      std::string s = request->args();
      istringstream istringname(s);
      
      istringname>> x>>y;
      
      uint32_t result = add(x,y);
      
      reply->set_success(true);
      reply->set_value(std::to_string(result));
    
    }else if(request->name() == "gettotal" || request->name() == "GETTOTAL"){

      reply->set_success(true);
      reply->set_value(std::to_string(total));
    
    }
    else{
    
      reply->set_success(false);
      reply->set_value("-1");
    
    }
    
    return Status::OK;
  }
};

void RunServer(std::string socket_addr) {
  intro();
  std::string server_address(socket_addr);
  AddRPCServiceServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register the Service
  builder.RegisterService(&service);
  // Assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. 
  server->Wait();
  
}
void help(){
  std::cout<<"\n*********************************";
  std::cout<<"\n\t Use ./rpcserv_server [port]";
  std::cout<<"\n*********************************\n";
  
}
int main(int argc, char** argv) {
  struct in_addr addr;

  if(argc<2){
    std::cout<<"\n===================";
    std::cout<<"\nInvalid Server Call ";
    std::cout<<"\n===================";
    help();
    return 0;
  }
  std::string socket_addr = "0.0.0.0:"; // Listen at all IP's
  std::string port_no = argv[1];
  
  socket_addr+=port_no;
  
  RunServer(socket_addr);

  return 0;
}

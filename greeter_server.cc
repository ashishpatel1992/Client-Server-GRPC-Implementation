/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 *
 */
// protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=grpc_cpp_plugin helloworld.proto
// protoc -I . --cpp_out=. ../../protos/helloworld.proto

#include <iostream>
#include <memory>
#include <string>
#include<bits/stdc++.h>

#include <grpcpp/grpcpp.h>


#include "helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;
static uint32_t total =0;
uint32_t add(uint32_t a, uint32_t b){
  total+= (a + b);
  return (a+b);
}
uint32_t gettotal(void){
  return (total);
}
using namespace std;
// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override {
    // std::string prefix("Hello ");
    if(request->name() == "add"){
      std::string s = request->args();
      uint32_t x,y;
      istringstream istringname(s);
      istringname>> x>>y;
      uint32_t result = add(x,y);
      reply->set_message("success");
      reply->set_value(std::to_string(result));
    }else if(request->name() == "gettotal"){
      reply->set_message("success");
      reply->set_value(std::to_string(total));
    }
    else{
      reply->set_message("Request for "+ request->name()+ " not found");
      reply->set_value("-1");
      // return Status::
    }
    
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}

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
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>


#include "helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status; 
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

#define MAX_MSG_SIZE 1024

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string& user, const std::string& data) {
    // Data we are sending to the server.
    HelloRequest request;
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
    HelloReply reply;
    // reply.SerializeToString()
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
  
    // The actual RPC.
    Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return (reply.message()+" "+reply.value());
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }

    // HelloRequest hr = HELLOREQUEST_INIT;
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char* argv[]) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  std::string user;
  user = argv[1];
  std::string args;
  
  for (int i = 2; i < argc; ++i){
        if(user == "add"){
            args = args+argv[i]+" ";
            // cout << argv[i] << "\n"; 
        }else break;
    } 
  
  std::string reply = greeter.SayHello(user,args);
  if(reply != "")
  if(user == "add")
    std::cout << "Sum received: " << reply <<"\n";
  else if(user == "gettotal")
    std::cout<<" Total is "<< reply<<"\n";
  else  std::cout<<" ";
  return 0;
}

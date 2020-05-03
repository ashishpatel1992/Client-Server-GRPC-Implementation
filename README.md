# Client Server GRPC implementation
This project Remote Procedure Call (RPC) between server and client in c++ using Google Protocol Buffer (Protobuf).
## 1. Introduction
RPC is a generic term for a function call that is serviced in a different address space than the callers.
RPC necessarily implements a protocol for the caller’s process, C, to encode the function name and arguments and send them to the servicing process, S, as well as for S to encode the return values and send them to C. In this assignment, the encoding will use serialization, a term for converting a language level data object to a sequence of bytes. The inverse operation – reconstituting a data object from a sequence of bytes (as stored on disk or sent over the network) – is called deserialization. Protobufs is precisely a framework for describing data objects and serializing/deserializing them.

# Problem Statement
## 2. RPC protocol
We'll be having two messages:
### a) Call
Here we have call which encapsulates the function invocation. The Call message consists of two required fields: the name of the function as a string, and the args (arguments) of the function as an array of bytes. The format of the message in Protobuf is as:
```c
message Call
{
required string name = 1;
required bytes args = 2;
}
```
### b) Return
Here return encapsulates the function return. The Return message consists of two required fields: the success of the RPC as a boolean, and the value returned by the function as an array of bytes. 
Format is:
```c
message Return
{
required bool success = 1;
required bytes value = 2;
}
```
The args and value byte arrays hold serialized content specific to a given function. Specifically, you must define additional Protobuf messages to describe each function’s argument list and return value (void argument lists and return values aside). The serialization of the Protobuf messagecorresponding to a function’s argument list is the value for Call’s args field; the serialization of the Protobuf message corresponding to a function’s return value is the value for Call’s args field; the serialization of the Protobuf message corresponding to a function’s return value is the value for Returns’s value field.

## 3. RPC
You must implement two functions as RPCs: add and gettotal. Implemented locally, the functions are:
```c
static uin32_t total = 0;
Uint32_t add(uint32_t a, uint32_t b)
{
    total += (a + b);
    return (a + b);
}
uin32_t gettotal(void)
{
    return (total);
}
```
Note :
1. You need not handle integer overflow.
2. Both RPCs are blocking; the caller waits for the RPC to return before calling another function,
whether local or remote.


## 4. Additional details
- This is a pair-programming lab. The server file and client file should be on different machines.
- You can use CLI to enter details for communication (Host address, binding port number) and
arguments for the add function with other required information.
- For byte array, unsigned char can be used by typedef -ing.

## 5. References
- https://github.com/protobuf-c/protobuf-c/wiki/Examples
- https://grpc.io/docs/tutorials/basic/cpp/
- https://developers.google.com/protocol-buffers/docs/cpptutorial

## 6. Contributers
Contributers in this project
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
   <tr>
      <td align="center"><a href="https://ashishpatel.dev"><img src="https://avatars3.githubusercontent.com/u/652311?v=4" width="100px;" alt=""/><br /><sub><b>Ashish Patel</b></sub></a></td>
      <td align="center"><a href="https://github.com/parikhnand"><img src="https://avatars3.githubusercontent.com/u/25660685?s=460&v=4" width="100px;" alt=""/><br /><sub><b>Nand Parikh</b></sub></a></td>
   </tr>
   
   
</table>

<!-- markdownlint-enable -->
<!-- prettier-ignore-end -->
<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://allcontributors.org) specification.
Contributions of any kind are welcome!



License
----

MIT
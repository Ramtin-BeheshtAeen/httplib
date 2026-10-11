#include <iostream>
#include <memory>

namespace httplib {

  struct Response;


class Result {
public:
  Result() = default;
  Result(std::unique_ptr<Response> &&res, Error err,
         Headers &&request_headers = Headers{})
      : res_(std::move(res)), err_(err),
    request_headers_(std::move(request_headers)) {}
};


class Server {
public:
  void say_hello() {};
};


class Client {
 public:
  // explicint unable the compiler to make it befor it is actually asked:
   explicit Client(const std::string &host, int port);
   Result Get(const std::string &path);
};



struct Response {
  std::string version;
  int status = -1;
  std::string reason;
  //Headers headers;
  //Headers trailers;
  std::string body;
  std::string location; // Redirect location

  
};
 
}

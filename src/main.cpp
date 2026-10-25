// dont know if this really affects me but the color of these includes are yellow on linux and the func definers like int are now purple also on linux
#include <cstdint>
#include <iostream>
#include "CppHTTPServer/req.hpp"
#include "CppHTTPServer/resp.hpp"
#include "CppHTTPServer/router.hpp"
#include "CppHTTPServer/tools.hpp"

int main (int argc, char *argv[]) {
  Router router;

  // router.logging_ = true;

  std::cout << router.logging_ << std::endl;

  int portNum = Tools::parse_args(argc, argv);

  if (portNum == -1){
    portNum = 8080;
  }

  router.get("/ping", [](const Req_lib::Request& req) {
    std::cout << req.raw_data << std::endl;
    return Resp::default_ok("ok", "text");
  });

  std::uint8_t good = router.StartServer();
  return good;

  /* =================== tcp code starts here ========================== */

  // int serverSocker = socket(AF_INET, SOCK_STREAM, 0);
  // if (serverSocker < 0) {
  //   std::cerr << "Error in creating connection\n";
  //   return 1;
  // }
  //
  // int opt = 1;
  // setsockopt(serverSocker, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  //
  // sockaddr_in serverAdress;
  //
  // serverAdress.sin_family = AF_INET;
  // serverAdress.sin_port = htons(portNum);
  // serverAdress.sin_addr.s_addr = INADDR_ANY;
  //
  // if ( bind(serverSocker, (struct sockaddr*)&serverAdress, sizeof(serverAdress)) < 0){
  //   std::cerr << "error binding socket\n";
  //   return 1;
  // }
  //
  // std::cout << "Now have connection at: " << portNum << "\n";
  //
  // listen(serverSocker, 5);
  //
  // Req_lib::Request request;
  //
  // // have to keep in mind at some point memory will have to be alterd from here
  // while(true){
  //   int clientSocket = accept(serverSocker, nullptr, nullptr);
  //
  //   char buffer[1024] = {0};
  //   size_t i = recv(clientSocket, buffer, sizeof(buffer), 0);
  //
  //   if(i > 0){
  //     std::cout << "\n";
  //     // std::cout << "Recived message: \n" << buffer << "\n";
  //     std::string s1 = buffer;
  //
  //     std::string parsed_meth = Tools::parse_recv_meth(s1);
  //
  //     if(parsed_meth == "NULL"){
  //       std::cerr << "Invalid method\n";
  //       return 1; // dont return but handle it some how
  //     }
  //
  //     std::string resp = Resp::default_ok("your type is " + parsed_meth, "json");
  //
  //     Req_lib::Request request = Req_lib::parse_req(buffer);
  //     std::cout << "Method: " << request.method << std::endl;
  //     std::cout << "Http version: " << request.HTTP_version << std::endl;
  //     std::cout << "Url Path: " << request.url_path << std::endl;
  //
  //     std::cout << "Host: " << request.header_map["Host"] << std::endl;
  //     std::cout << "User-Agent: " << request.header_map["User-Agent"] << std::endl;
  //     std::cout << "Accept: " << request.header_map["Accept"] << std::endl;
  //
  //     if (Tools::map_containes(request.header_map, "Origin")){
  //       std::cout << "Origin: " << request.header_map["Origin"] << std::endl;
  //     }
  //
  //     send(clientSocket, resp.data(), resp.length(), 0);
  //   }else{
  //     std::cerr << "idk somthing wrong I think\n";
  //   }
  //   close(clientSocket);
  // }
  //
  // close(serverSocker); // final last minute closing of the server socket connection
  // return 0;
}

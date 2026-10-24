#include "CppHTTPServer/router.hpp"
#include "CppHTTPServer/req.hpp"
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include "CppHTTPServer/resp.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include "CppHTTPServer/tools.hpp"

void Router::get(const std::string& path, Handler h){
  // get_routes_[path] = "GET"; // i think so 
  routes_["GET"][path] = std::move(h);
}

// dont actually know what this is for 
std::string Router::dispatch(const Req_lib::Request& req) const {
  auto m = routes_.find(req.method);
  if (m == routes_.end()) return Resp::not_found();

  auto h = m->second.find(req.url_path);
  if (h == m->second.end()) return Resp::not_found();

  return h->second(req);
}

//TODO: ok so the order this needs to work is to check the map for the path of the request from the routers req map then follow the handler given for the http get request
bool Router::StartServer(const std::string& port){
  //NOTE one day will have to handle shutdowns as this thing grows
  int portNum = default_port;

  try {
    size_t pos = 0;
    int value = std::stoi(port, &pos);

    if (pos != port.size() || value < 1 || value > 65535) {
      throw std::invalid_argument("invalid port: " + port);
    }
    portNum = value;
  } catch (const std::exception& e) {
    // covers invalid_argument and out_of_range
    std::cerr << "Bad port '" << port << "', using default 8080\n";
  }

  int serverSocker = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocker < 0) {
    std::cerr << "Error in creating connection\n";
    return 1;
  }

  int opt = 1;
  setsockopt(serverSocker, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  sockaddr_in serverAdress;

  serverAdress.sin_family = AF_INET;
  serverAdress.sin_port = htons(portNum);
  serverAdress.sin_addr.s_addr = INADDR_ANY;

  if ( bind(serverSocker, (struct sockaddr*)&serverAdress, sizeof(serverAdress)) < 0){
    std::cerr << "error binding socket\n";
    return 1;
  }

  std::cout << "Now have connection at: " << portNum << "\n";

  listen(serverSocker, 5);

  Req_lib::Request request;

  // have to keep in mind at some point memory will have to be alterd from here
  while(true){
    int clientSocket = accept(serverSocker, nullptr, nullptr);

    char buffer[1024] = {0};
    size_t i = recv(clientSocket, buffer, sizeof(buffer), 0);

    if(i > 0){
      std::cout << "\n";
      // std::cout << "Recived message: \n" << buffer << "\n";
      std::string s1 = buffer;

      std::string parsed_meth = Tools::parse_recv_meth(s1);

      if(parsed_meth == "NULL"){
        std::cerr << "Invalid method\n";
        return 1; // dont return but handle it some how
      }

      std::string resp = Resp::default_ok("your type is " + parsed_meth, "json");

      Req_lib::Request request = Req_lib::parse_req(buffer);

      send(clientSocket, resp.data(), resp.length(), 0);
    }else{
      std::cerr << "idk somthing wrong I think\n";
    }
    close(clientSocket);
  }

  close(serverSocker); // final last minute closing of the server socket connection
  return 0;
}

Router::Router(bool logging) : logging_(logging){

}

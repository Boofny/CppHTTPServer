#include <CppHTTPServer/router.hpp>
#include <iostream>

Router::Router(std::string mode, bool cors, bool logging) : mode_(mode), cors_(cors), logging_(logging){}

Router::~Router(){}

void Router::Start(const std::string& port_num){ // where the engine will live
  port = port_num;
  std::cout << port << std::endl;
}

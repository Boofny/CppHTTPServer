#include <CppHTTPServer/router.hpp>
#include <iostream>

CppHTTP::CppHTTP(std::string mode, bool cors, bool logging) : mode_(mode), cors_(cors), logging_(logging){}

CppHTTP::~CppHTTP(){}

void CppHTTP::Start(const std::string& port_num){ // where the engine will live
  port = port_num;
  std::cout << port << std::endl;
}

CppHTTP Router::New(){
  return CppHTTP{};
}

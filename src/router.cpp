#include "CppHTTPServer/router.hpp"
#include "CppHTTPServer/req.hpp"
#include <iostream>
#include <unordered_map>
#include <utility>
#include "CppHTTPServer/resp.hpp"

void Router::get(const std::string& path, Handler h){
  get_routes_[path] = "GET"; // i think so 

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

void Router::StartServer(const std::string& port){
  std::cout << port << std::endl;
}

#include "CppHTTPServer/router.hpp"
#include "CppHTTPServer/req.hpp"
#include <unordered_map>
#include <utility>
#include "CppHTTPServer/resp.hpp"

void Router::get(const std::string& path, Handler h){
  routes_["GET"][path] = std::move(h);
}

std::string Router::dispatch(const Req_lib::Request& req) const {
  auto m = routes_.find(req.method);
  if (m == routes_.end()) return Resp::not_found();

  auto h = m->second.find(req.url_path);
  if (h == m->second.end()) return Resp::not_found();

  return h->second(req);
}

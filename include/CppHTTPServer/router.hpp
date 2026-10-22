#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include "CppHTTPServer/req.hpp"

using Handler = std::function<std::string(const Req_lib::Request&)>;

class Router{
  public:
    void get(const std::string& path, Handler h);
    std::string dispatch(const Req_lib::Request& req) const;

  private:
    std::unordered_map<std::string, std::unordered_map
      <std::string, Handler>> routes_;

};

#pragma once
#include <string>
#include <map>

namespace Req_lib {
  struct Request{ //  for now only worry about curl and get req
    std::string method, url_path, HTTP_version;
    std::map<std::string, std::string> header_map;
  };

  struct Request;
  Request parse_req(const std::string& request);
}

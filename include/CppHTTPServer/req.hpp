#pragma once
#include <string>
#include <map>

namespace Req_lib {
  struct Request{ //  for now only worry about curl and get req
    std::string method, url_path, HTTP_version;
    std::map<std::string, std::string> header_map;
    const char* raw_data;
    std::size_t length;
  };

  // struct Request; wtf is this? 
  Request parse_req(const std::string& request);
}

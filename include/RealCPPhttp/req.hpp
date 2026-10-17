#pragma once
#include <string>


namespace Req_lib {
  struct Request{ //  for now only worry about curl and get req
    std::string method, url_path, HTTP_version, Host, Agent, Accept;  
  };

  struct Request;
  Request parse_req(const std::string& request);
}

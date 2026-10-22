#pragma once
#include <string>

namespace Resp {
  std::string default_ok(const std::string& msg, const std::string& cont_type);
  inline std::string not_found(){
    return "NULL";
  }
}

#pragma once
#include <string>

namespace Resp {
  std::string default_ok(const std::string& msg, const std::string& cont_type);
  std::string default_error(std::string_view msg, const int& err_code);
  inline std::string not_found(){
    return "NULL";
  }
}

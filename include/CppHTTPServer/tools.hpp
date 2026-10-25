#pragma once
#include <string>
#include <map>

namespace Tools {
  int parse_args(int argc, char *args[]); // pass by pointer brotha!
  // the const and referance means this will just be read and built for something else
  std::string parse_recv_meth(std::string_view in); // pass by referance
  bool map_containes(const std::map<std::string, std::string> &header_map, std::string find_key);
};

namespace Meth{
  const std::string GET = "GET";
  const std::string POST = "POST";
  const std::string DELETE = "DELETE";
  const std::string PUT = "PUT";

  const std::string meth_list[4] = {GET, POST, PUT, DELETE};
}


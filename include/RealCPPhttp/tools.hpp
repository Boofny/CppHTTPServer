#pragma once
#include <string>

namespace Tools {
  int parse_args(int argc, char *args[]); // pass by pointer brotha!
  // the const and referance means this will just be read and built for something else
  std::string parse_recv_meth(std::string& in); // pass by referance

};

namespace Meth{
  const std::string GET = "GET";
  const std::string POST = "POST";
  const std::string DELETE = "DELETE";
  const std::string PUT = "PUT";

  const std::string meth_list[4] = {GET, POST, PUT, DELETE};
}


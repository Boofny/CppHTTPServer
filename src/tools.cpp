#include <climits>
#include <iostream>
#include <cctype>
#include <json/value.h>
#include <stdexcept>
#include <string>
#include "CppHTTPServer/tools.hpp"
#include <json/json.h>
#include <map>

// bool Tools::map_containes(std::map<std::string, std::string> header_map, std::string find_key);
bool Tools::map_containes(const std::map<std::string, std::string>& header_map, std::string find_key);

// valid_port is used to to validate a port from its value and length
static bool valid_port(const std::string &in){
  if (in.empty()){
    std::cerr << "No port given\n";
    return false;
  }

  if (in.length() > 0 && in.length() > 5){
    std::cerr << "Invalid port\n";
    return false;
  }

  int conv_val;

  try {
    conv_val = std::stoi(in);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what();
    std::cerr << "Invalid input\n";
    return false;
  } catch (const std::out_of_range& e){
    // std::cout << e.what();
    std::cerr << "Out of range\n";
    return false;
  }

  if (conv_val > USHRT_MAX || conv_val < 0) {
    std::cerr << "Invalid port\n";
    return false;
  }

  return true;
}

// Checks if a string is a number
static bool is_number(const std::string& in){
  for (char letter : in){
    if (!std::isdigit(letter)){
      return false;
    }
  }

  return true;
}

int Tools::parse_args(int argc, char *argv[]){
  if (argc < 2 || argv == nullptr){
    return -1;
  }

  std::string portNum;

  for (int i = 0; i < argc; i++){
    if (std::string(argv[i]) == "-p" && argv[i+1] != nullptr) {
      portNum = argv[i+1];
      break;
    }
  }

  int real_port = -1;

  if (portNum != "") {
    if (!is_number(portNum) && !valid_port(portNum)) {
      std::cerr << "Invalid input brotha!\n";
      return -1;
    }

    try {
      real_port = std::stoi(portNum);
    } catch (const std::invalid_argument& e) {
      std::cerr << "Invalid argument\n";
      return -1;
    }

  }

  return real_port;
}

// pass by reference the input brother
std::string Tools::parse_recv_meth(std::string& in) {

  // this is what is sent from a normal get req
  // GET / HTTP/1.1
  // Host: localhost:8080
  // User-Agent: curl/8.22.0
  // Accept: */*

  // and with a path after localhost:8080/hello
  // GET /hello HTTP/1.1
  // Host: localhost:8080
  // User-Agent: curl/8.22.0
  // Accept: */*

  for(std::string meth : Meth::meth_list){
    int found = in.find(meth);
    if (found != -1){
      // std::cout << "Method found: " << meth << "\n";
      return meth;
    }
  }

  return "NULL"; // will return method type
}

// Response
// HTTP/1.1 200 OK
// Content-Type: application/json
// Content-Length: 30
// Connection: close

// Request
// GET / HTTP/1.1
// Host: localhost:8080
// User-Agent: curl/8.22.0
// Accept: */*

// should make something like breakdown resp and req into structs

bool Tools::map_containes(const std::map<std::string, std::string>& header_map, std::string find_key){
  return header_map.count(find_key) > 0;
}


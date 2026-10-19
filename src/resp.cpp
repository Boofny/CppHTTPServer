#include <json/writer.h>
#include <json/value.h>
#include <json/json.h>
#include <iostream>
#include <string>
#include "RealCPPhttp/resp.hpp"

static std::string create_json_default_resp(const std::string& msg);

// Response from this server 
// HTTP/1.1 200 OK
// Content-Type: application/json
// Content-Length: 30
// Connection: close

// default_ok is just the default_ok resp with a custom message in text/plain NOT json
std::string Resp::default_ok(const std::string& msg, const std::string& cont_type) {

  // std::cout << "using type " + cont_type << std::endl;

  std::string resp;
  std::string return_msg;
  resp.reserve(128 + msg.size());

  std::string meth_type;

  resp += "HTTP/1.1 200 OK\r\n"; // also need to handle url paths but will deal with it later

  if(cont_type == "text"){
    meth_type = "text/plain";
    return_msg = msg;

  }else if(cont_type == "json"){
    meth_type = "application/json";
    return_msg = create_json_default_resp(msg);

  }else{

    std::cerr << "Invalid type of content\n";
    return "NULL";
  }

  resp += "Content-Type: " + meth_type + "\r\n";

  resp += "Content-Length: " + std::to_string(return_msg.size()) + "\r\n";
  resp += "Connection: close\r\n"; // NOTE: this does work for now but will need to actually make a router in order to do this propely
  resp += "Access-Control-Allow-Origin: http://localhost:5500\r\r";
  resp += "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\r\n"; 
  resp += "Access-Control-Allow-Headers: Content-Type\r\n";
  resp += "\r\n";
  resp += return_msg;

  return resp;
}

// will be used to format and parse the inputed json structure used
static std::string create_json_default_resp(const std::string& msg){
  Json::Value user;

  user["message"] = msg;
  Json::StreamWriterBuilder w;
  w["indentation"] = ""; 

  // std::cout << "Default ok json value: " << user << std::endl;

  return Json::writeString(w, user);
}







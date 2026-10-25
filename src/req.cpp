#include "CppHTTPServer/req.hpp"
#include "CppHTTPServer/tools.hpp"
#include <cstddef>
#include <iostream>
#include <map>
// #include <ostream>
#include <stdexcept>
#include <string>

// Request from browser
// GET /ping HTTP/1.1
// Host: localhost:8080
// Connection: keep-alive
// sec-ch-ua: "Brave";v="155", "Chromium";v="155", "Not(A:Brand";v="24"
// sec-ch-ua-mobile: ?0
// sec-ch-ua-platform: "Windows"
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/155.0.0.0 Safari/537.36
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/jxl,image/avif,image/webp,image/apng,*/*;q=0.8
// Sec-GPC: 1
// Sec-Fetch-Site: none
// Sec-Fetch-Mode: navigate
// Sec-Fetch-User: ?1
// Sec-Fetch-Dest: document
// Accept-Encoding: gzip, deflate, br, zstd
// Accept-Language: en-US,en;q=0.8

// Request from curl
// GET / HTTP/1.1
// Host: localhost:8080
// User-Agent: curl/8.22.0
// Accept: */*

std::map<std::string, std::string> parse_headers(std::string req);

Req_lib::Request Req_lib::parse_req(const std::string& request){
  Req_lib::Request new_request;

  for(std::string meth : Meth::meth_list){
    int found = request.find(meth);
    if (found != -1){
      new_request.method = meth;
      break;
    }
  }

  new_request.raw_data = request.data();
  new_request.length = request.length();

  size_t url_start_range = request.find(' ');
  if(url_start_range == std::string::npos) { return {};}
  url_start_range++;

  size_t url_end_range = request.find(' ', url_start_range);
  if(url_end_range == std::string::npos) { return {};}

  // start pos, length of the word 
  new_request.url_path = request.substr(url_start_range, url_end_range - url_start_range);
  
  // ============

  size_t http_v_start = request.find(' ', url_end_range);
  if(http_v_start == std::string::npos) { return {};}
  http_v_start++;

  size_t http_v_end = request.find("\r\n", http_v_start);
  if(http_v_end == std::string::npos) { return {};}

  new_request.HTTP_version = request.substr(http_v_start, http_v_end - http_v_start);

  // ============ from here bellow call can be a function call to reduce code

  // std::cout << "Request method: [" << new_request.method << "]\n";
  if(new_request.HTTP_version != "HTTP/1.1"){
    throw std::invalid_argument("Must be using HTTP version 1.1");
  }

  std::map<std::string, std::string> maps = parse_headers(request);
  new_request.header_map = maps;
  std::cout << "Request: \n" << request;

  return new_request;
}

// parse_headers is used for parsing the entire string of request appart from the first request line
std::map<std::string, std::string> parse_headers(std::string req){
  std::string seperator = "\r\n";
  size_t first_line_end = req.find(seperator);
  if(first_line_end == std::string::npos){
    return {};
  }
  first_line_end += seperator.length();

  std::string subber = req.substr(first_line_end);

  std::map<std::string, std::string> header_map;
  std::string temp_req = subber;
  temp_req.erase(temp_req.length() - seperator.length(), temp_req.length()); // just trim the last char
  size_t pos;

  while((pos = temp_req.find(seperator)) != std::string::npos){
    std::string stringer = temp_req.substr(0, pos);

    size_t splitter = stringer.find(':');
    if(splitter == std::string::npos) {return {};}

    std::string key = stringer.substr(0, splitter);

    std::string val = stringer.substr(splitter+2, stringer.find(seperator));

    // std::cout << "[" << key << "] " << "[" << val << "]\n";

    header_map.insert({key, val});

    temp_req.erase(0, pos + seperator.length());
  }
  
  return header_map;
}





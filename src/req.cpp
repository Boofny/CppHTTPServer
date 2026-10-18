#include "RealCPPhttp/req.hpp"
#include "RealCPPhttp/tools.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>

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

// struct Request{
//   std::string 
//   method,  [X] done 
//   url_path,  [X] done
//   HTTP_version, [X] done
//   Host,  [X] done
//   Agent, 
//   Accept;  
// };

std::string parse_header(std::string req, std::string header);

Req_lib::Request Req_lib::parse_req(const std::string& request){
  Req_lib::Request new_request;

  for(std::string meth : Meth::meth_list){
    int found = request.find(meth);
    if (found != -1){
      new_request.method = meth;
      break;
    }
  }

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

  new_request.Host = parse_header(request, "Host:");
  new_request.Agent = parse_header(request, "User-Agent:");
  new_request.Accept = parse_header(request, "Accept:");

  std::cout << "Host: [" << new_request.Host << "]\n";
  std::cout << "Agent: [" << new_request.Agent << "]\n";
  std::cout << "Accept: [" << new_request.Accept << "]\n";

  // ============

  std::cout << "Request method: [" << new_request.method << "]\n";
  if(new_request.HTTP_version != "HTTP/1.1"){
    throw std::invalid_argument("Must be using HTTP version 1.1");
  }

  std::cout << "Http version: [" << new_request.HTTP_version << "]\n";
  std::cout << "Req path: [" << new_request.url_path << "]\n";

  std::cout << "\nRequest: \n" << request << std::endl;
  return new_request;
}

// parse_header() is for parsing and finding individual header values for http requests
std::string parse_header(std::string req, std::string header){
  size_t start_range = req.find(' ', req.find(header));
  if(start_range== std::string::npos) {return {};}
  start_range++;

  size_t end_range = req.find("\r\n", start_range);
  if(end_range == std::string::npos) {return {};}
  return req.substr(start_range, end_range - start_range);
}







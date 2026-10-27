#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include "CppHTTPServer/req.hpp"

using Handler = std::function<std::string(const Req_lib::Request&)>;

class Router{
  public:
    Router(bool logging = false);
    void get(const std::string& path, Handler h);


    bool StartServer(const std::string& path = "8080");

    bool logging_;

  private:
    std::string dispatch(const Req_lib::Request& req) const;
    static constexpr int default_port = 8080;
    std::unordered_map<std::string, std::string> get_routes_; // using this just for now

    std::unordered_map<std::string, std::unordered_map <std::string, Handler>> routes_; // thi creates a map of maps best for different methods
};

// example from golive
// package main
//
// import (
// 	"net/http"
// 	"github.com/Boofny/golive"
// 	"github.com/Boofny/golive/middleware"
// )
//
// func main() {
// 	e := golive.Launch()
//
// 	e.Chain(middleware.CORS())
//
// 	e.GET("/ping", func(c *golive.Context)error{
// 		return c.SendSTRING(http.StatusOK, "pong") //send out your data
// 	})
//
// 	e.StartServer(":8080")
// }

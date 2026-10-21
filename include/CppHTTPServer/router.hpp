#pragma once
#include <string>

namespace Router_lib{ }

class Router{
  public:
    Router(std::string mode = "default", bool cors = false, bool logging = false);
    ~Router();

    std::string mode_;
    bool cors_;
    bool logging_;

    void Start(const std::string& port = "8080");

    void Get(std::string path);

  private:
    std::string port;
};


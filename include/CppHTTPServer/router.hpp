#pragma once
#include <string>


class CppHTTP{
  public:
    CppHTTP(std::string mode = "default", bool cors = false, bool logging = false);
    ~CppHTTP();

    std::string mode_;
    bool cors_;
    bool logging_;

    void Start(const std::string& port = "8080");

    void Get(std::string path);

  private:
    std::string port;
};

namespace Router{ 
  CppHTTP New();
}

#pragma once

#include <exception>
#include <string>

class ErrorParams: public std::exception {
public:
    ErrorParams(const std::string &msg);
    ErrorParams(const char *msg);
    const char* what();

private:
    std::string _msg;
};


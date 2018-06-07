#pragma once

#include <exception>
#include <string>
#include <memory>

class ErrorParams: public std::exception {
public:
    ErrorParams(std::string &msg);
    ErrorParams(const char *msg);
    const char* what();

private:
    std::string _msg = "Fatal - talospuzzle command line error: ";
};


#pragma once

#include <exception>
#include <string>

class Errors: 
    public std::exception {
public:
    Errors(const std::string& msg);
    Errors(const char* msg);
    const char* what();

private:
    std::string _msg;
};

inline const char* Errors::what() { return _msg.c_str(); }

class ErrorParams: 
    public Errors {
public:
    using Errors::Errors;
};

class ErrorMatrix: 
    public Errors {
public:
    using Errors::Errors;
};
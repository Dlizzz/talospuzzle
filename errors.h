#pragma once

#include <exception>
#include <string>

class Errors: 
    public std::exception {
public:
    Errors(const std::string& msg);
    Errors(const char* msg);
    virtual const char* what() const;

private:
    std::string _msg;
};

inline const char* Errors::what() const { return _msg.c_str(); }

class ErrorParams: 
    public Errors {
public:
    using Errors::Errors;
};

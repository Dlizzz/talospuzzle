#pragma once

#include <exception>
#include <string>

class ErrorParams: 
    public std::exception {
public:
    explicit ErrorParams(const std::string& msg) noexcept;
    explicit ErrorParams(const char* msg) noexcept;
    virtual ~ErrorParams() noexcept {}
    virtual const char* what() const noexcept { return _msg.c_str(); }

protected:
    std::string _msg;
};

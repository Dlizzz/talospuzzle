#pragma once

#include <exception>
#include <string>

class ErrorParams: 
    public std::exception {
public:
    explicit ErrorParams(const std::string& msg) noexcept;
    explicit ErrorParams(const char* msg) noexcept;
    ~ErrorParams() noexcept override = default;
    const char* what() const noexcept override { return _msg.c_str(); }

protected:
    std::string _msg;
};

#pragma once

#include <exception>
#include <string>

class ErrorBase: 
    public std::exception {
public:
    explicit ErrorBase(const std::string& msg) noexcept;
    explicit ErrorBase(const char* msg) noexcept;
    ~ErrorBase() noexcept override = default;
    const char* what() const noexcept override { return _msg.c_str(); }

protected:
    std::string _msg;
};

class ErrorParams: 
    public ErrorBase {
public:
    explicit ErrorParams(const std::string& msg) noexcept;
    explicit ErrorParams(const char* msg) noexcept;
};

class ErrorStats: 
    public ErrorBase {
public:
    explicit ErrorStats(const std::string& msg) noexcept;
    explicit ErrorStats(const char* msg) noexcept;
};

class ErrorImages: 
    public ErrorBase {
public:
    explicit ErrorImages(const std::string& msg) noexcept;
    explicit ErrorImages(const char* msg) noexcept;
};

#pragma once

#include <exception>
#include <string>

// HTML Colors helpers
class ErrorColor: 
    public std::exception {
public:
    explicit ErrorColor(const std::string& msg) noexcept: _msg(msg) {}
    explicit ErrorColor(const char* msg) noexcept: _msg(msg) {}
    virtual ~ErrorColor() noexcept {}
    virtual const char* what() const noexcept { return _msg.c_str(); }

protected:
    std::string _msg;
};

struct ColorValues {
    unsigned int hexValue;
    unsigned char redValue;
    unsigned char greenValue;
    unsigned char blueValue;
};

bool isValidHtmlColorName(const std::string& colorName) noexcept;

ColorValues htmlColorNameToValues(const std::string& colorName);

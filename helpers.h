#pragma once

#include <exception>
#include <string>

// HTML Colors helpers
class ErrorColor: 
    public std::exception {
public:
    ErrorColor(const char* msg) noexcept;
};

struct ColorValues {
    unsigned int hexValue;
    unsigned char redValue;
    unsigned char greenValue;
    unsigned char blueValue;
};

bool isValidHtmlColorName(const std::string& colorName) noexcept;

ColorValues htmlColorNameToValues(const std::string& colorName);

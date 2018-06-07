#pragma once

#include <exception>
#include <string>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#pragma warning (push)
#include <boost/filesystem.hpp>
#pragma warning (pop)


// HTML Colors helper
class ErrorColor: public std::exception {
public:
    ErrorColor(const char* msg) noexcept;
};

struct ColorValues {
    unsigned int hexValue;
    unsigned char redValue;
    unsigned char greenValue;
    unsigned char blueValue;
};

bool isValidHtmlColorName(std::string colorName) noexcept;

ColorValues htmlColorNameToValues(std::string colorName);

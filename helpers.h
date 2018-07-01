#pragma once

#include <exception>
#include <string>
#include <iostream>

// Ascii drawing components
enum DrawingComponents: char {
    BLOCK = char(219), 
    BOTTOM_LEFT_CORNER = char(200),
    TOP_LEFT_CORNER = char(201),
    BOTTOM_RIGHT_CORNER = char(188),
    TOP_RIGHT_CORNER = char(187),
    HORIZONTAL_BAR = char(205),
    VERTICAL_BAR = char(186),
    NOTHING = char(32),
    EMPTY = char(250),
    UNDERLINE = char(238)
};

// HTML Colors helpers
class ErrorColor: 
    public std::exception {
public:
    explicit ErrorColor(const std::string& msg) noexcept: _msg(msg) {}
    explicit ErrorColor(const char* msg) noexcept: _msg(msg) {}
    ~ErrorColor() noexcept override = default;
    const char* what() const noexcept override { return _msg.c_str(); }

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

// Ascii drawing helper
void coutColoredBlock(const ColorValues& color);

#pragma once

#include <exception>
#include <string>
#include <vector>

/*  
Pattern helpers
Pattern are 2d arrays (rows, cols), using vector of vector 
*/

/*
Return a 90° rotated copy of the given pattern
*/
template <class T> std::vector<std::vector<T>> rot90(const std::vector<std::vector<T>> &in) {
    // Outer vector elements are lines, inner vectors elements are columns
    // All inner vectors must have the same size
    std::vector<std::vector<T>> out;
    std::vector<T> outColumn;
    long long inRows, inColumns;

    // Get size (rows, cols) of 'in' 
    // Columns number comes from first line (assuming same number for each line)
    inRows = in.size();
    inColumns = in.front().size();

    // Iterate over 'out' to populate from 'in'
    out.reserve(inColumns);
    for (long long outRow = 0; outRow < inColumns; outRow++) {
        // New empty column  for out
        outColumn.clear();
        outColumn.reserve(inRows);
        for (long long outCol = 0; outCol < inRows; outCol++) {
            outColumn.push_back(in[outCol][inColumns - 1 - outRow]);
        }
        out.push_back(outColumn);
    }
    
    return out;
}

// HTML Colors helpers
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

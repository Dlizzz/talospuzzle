#include <iostream>

#include "piece.h"
#include "piecesbag.h"

using namespace std;

std::ostream& operator<<(std::ostream& out, const PiecesBag& bag) {
    for (auto& piece : bag) { out << piece.second; }
    return out;
}

PiecesBag piecesBag {
    {"l-right", { "L Right", 1, "DarkOrange", {
        {1, 1},
        {1, 0},
        {1, 0}
    }}},
    {"l-left", { "L Left", 2, "Tomato", {
        {1, 1},
        {0, 1}, 
        {0, 1}
    }}},
    {"step-right", { "Step Right", 3, "Lime", {
        {0, 1, 1},
        {1, 1, 0}
    }}},
    {"step-left", { "Step Left", 4, "SpringGreen", {
        {1, 1, 0},
        {0, 1, 1}
    }}},
    {"square", { "Square", 5, "Crimson", { 
        {1, 1}, 
        {1, 1} 
    }}}, 
    {"bar", { "Bar", 6, "DarkViolet", {
        {1, 1, 1, 1}
    }}},
    {"tee", { "Tee", 7, "Cyan", {
        {0, 1, 0},
        {1, 1, 1}
    }}}
};
